/*
 * client.c -- TCP client for versioned Remote File System (RFS)
 *
 * Practicum II - CS5600
 *
 * Description:
 *   This client program connects to a multi-threaded TCP server to perform
 *   remote file system operations with versioning support. Supported commands:
 *
 *   1. WRITE local_file remote_file
 *        - Upload a local file from the client to the server.
 *        - If the remote file exists, the server may keep older versions
 *          with timestamped filenames.
 *
 *   2. GET remote_file [version] local_file
 *        - Download a file from the server to the client.
 *        - Optionally specify a version to retrieve a specific historical version.
 *        - If local_file is omitted, the remote filename is used.
 *
 *   3. RM remote_file
 *        - Remove a file from the server.
 *
 *   4. LS remote_file
 *        - List all available versions of a file on the server.
 *
 *   5. STOP
 *        - Gracefully stop the server.
 *
 * Author: Zhimin Wang
 * Date: 11/28/2025
 */

#include "rfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"

// Main function for the RFS client.
// Handles commands: WRITE, GET, RM, LS, STOP.
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s [WRITE|GET|RM|LS|STOP] ...\n", argv[0]);
        return 1;
    }

    char *command = argv[1];

    // ----------------- Create TCP socket -----------------
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[CLIENT] Socket creation failed");
        return 1;
    }

    // ----------------- Server address setup -----------------
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // ----------------- Connect to server -----------------
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("[CLIENT] Connection failed");
        close(sock);
        return 1;
    }

    printf("[CLIENT] Connected to server.\n");

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    // ----------------- STOP command -----------------
    if (strcmp(command, "STOP") == 0) {
        send(sock, STOP_CMD, strlen(STOP_CMD), 0);

        int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (n > 0) {
            buffer[n] = '\0';
            printf("%s\n", buffer);
        }

        close(sock);
        return 0;
    }

    // ----------------- WRITE command -----------------
    if (strcmp(command, "WRITE") == 0) {

        if (argc < 4) {
            fprintf(stderr, "[CLIENT] WRITE requires local_file and remote_file\n");
            close(sock);
            return 1;
        }

        char *local_file = argv[2];
        char *remote_file = argv[3];

        FILE *fp = fopen(local_file, "rb");
        if (!fp) { perror("[CLIENT] Cannot open local file"); close(sock); return 1; }

        snprintf(buffer, sizeof(buffer), "WRITE %s", remote_file);
        send(sock, buffer, strlen(buffer), 0);

        int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0) { fclose(fp); close(sock); return 1; }
        buffer[n] = '\0';

        if (strncmp(buffer, "READY", 5) != 0) {
            printf("[CLIENT] Server: %s\n", buffer);
            fclose(fp);
            close(sock);
            return 1;
        }

        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
            send(sock, buffer, bytes_read, 0);
        }

        fclose(fp);
        printf("[CLIENT] File '%s' uploaded as '%s'\n", local_file, remote_file);
    }

    // ----------------- GET command -----------------
    else if (strcmp(command, "GET") == 0) {

        if (argc < 3) {
            fprintf(stderr, "[CLIENT] GET requires remote_file\n");
            close(sock);
            return 1;
        }

        char *remote_file = argv[2];
        char *version = NULL;
        char *local_file = NULL;

        if (argc == 3) {
            local_file = remote_file; // default output name
        }
        else if (argc == 4) {
            local_file = argv[3]; // GET remote_file local_file
        }
        else if (argc == 5) {
            version = argv[3];    // GET remote_file version local_file
            local_file = argv[4];
        }

        if (version)
            snprintf(buffer, sizeof(buffer), "GET %s %s %s", remote_file, version, local_file);
        else
            snprintf(buffer, sizeof(buffer), "GET %s %s", remote_file, local_file);

        send(sock, buffer, strlen(buffer), 0);

        int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0) { close(sock); return 1; }
        buffer[n] = '\0';

        if (strncmp(buffer, "READY", 5) != 0) {
            printf("[CLIENT] Server: %s\n", buffer);
            close(sock);
            return 1;
        }

        FILE *fp = fopen(local_file, "wb");
        if (!fp) { perror("[CLIENT] Cannot write local file"); close(sock); return 1; }

        ssize_t bytes;
        while ((bytes = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
            fwrite(buffer, 1, bytes, fp);
            if (bytes < sizeof(buffer)) break;
        }

        fclose(fp);
        printf("[CLIENT] File '%s' downloaded as '%s'\n", remote_file, local_file);
    }

    // ----------------- RM command -----------------
    else if (strcmp(command, "RM") == 0) {

        if (argc < 3) {
            fprintf(stderr, "[CLIENT] RM requires remote_file\n");
            close(sock);
            return 1;
        }

        snprintf(buffer, sizeof(buffer), "RM %s", argv[2]);
        send(sock, buffer, strlen(buffer), 0);

        int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (n > 0) {
            buffer[n] = '\0';
            printf("[CLIENT] Server response: %s\n", buffer);
        }
    }

    // ----------------- LS command -----------------
    else if (strcmp(command, "LS") == 0) {

        if (argc < 3) {
            fprintf(stderr, "[CLIENT] LS requires remote_file\n");
            close(sock);
            return 1;
        }

        snprintf(buffer, sizeof(buffer), "LS %s", argv[2]);
        send(sock, buffer, strlen(buffer), 0);

        printf("[CLIENT] Versions of '%s':\n", argv[2]);

        int n;
        while ((n = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
            buffer[n] = '\0';
            printf("%s", buffer);
            if (n < sizeof(buffer) - 1) break;
        }

        printf("\n");
    }

    else {
        fprintf(stderr, "[CLIENT] Unknown command: %s\n", command);
    }

    close(sock);
    return 0;
}
