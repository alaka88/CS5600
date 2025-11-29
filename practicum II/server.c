/*
 * server.c -- Multi-threaded TCP server for versioned Remote File System (RFS)
 *
 * Practicum II - CS5600
 *
 * Description:
 *   This server program implements a multi-threaded TCP-based Remote File System
 *   with file versioning and basic concurrency control. It listens for client
 *   connections and handles requests for file operations.
 *
 * Supported commands:
 *   1. WRITE local_file remote_file
 *        - Receives a file from a client and saves it on the server.
 *        - If the file already exists, the previous version is renamed with
 *          a timestamp before overwriting.
 *        - File locks are used to prevent corruption from concurrent writes.
 *
 *   2. GET remote_file [version] local_file
 *        - Sends the requested file to the client.
 *        - Supports optional version parameter to retrieve a historical version.
 *
 *   3. RM remote_file
 *        - Deletes a file from the server.
 *        - Returns a success or failure status to the client.
 *
 *   4. LS remote_file
 *        - Lists all versions of a file stored on the server.
 *        - Provides timestamped filenames for version history.
 *
 * Features:
 *   - Multi-threaded: each client connection is handled in a separate thread.
 *   - Concurrency control: mutexes and file locks ensure safe access to files.
 *   - Safe shutdown: handles SIGINT (Ctrl-C) to close sockets and terminate gracefully.
 *   - Disk space check: validates available storage before accepting new uploads.
 *   - Versioning: preserves old versions of files when overwritten.
 *
 * Directory:
 *   All server files are stored under a root directory (e.g., "server_files").
 *
 * Usage:
 *   ./server
 *   - Server listens on a configurable TCP port (default: 2000)
 *   - Waits continuously for client connections
 *
 * Author: Zhimin Wang
 * Date: 11/27/2025
 */

#include "rfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>
#include <sys/statvfs.h>
void handle_stop_request();

int server_socket;
pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;

// ----------Locks a file for writing----------
int lock_file(int fd) {
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    return fcntl(fd, F_SETLKW, &fl);
}

// ----------Unlocks a previously locked file----------
int unlock_file(int fd) {
    struct flock fl;
    fl.l_type = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    return fcntl(fd, F_SETLK, &fl);
}

// ---------- SIGINT handler ----------
void handle_sigint(int sig) {
    printf("\n[SERVER] Caught SIGINT. Cleaning up...\n");
    close(server_socket);
    pthread_mutex_destroy(&global_mutex);
    exit(0);
}

// ---------- Disk space check ----------
int check_disk_space(const char* path, size_t required) {
    struct statvfs fs;
    if (statvfs(path, &fs) != 0) return 0;
    size_t free_bytes = fs.f_bsize * fs.f_bavail;
    return free_bytes >= required;
}


// ---------- Handles one client's request (WRITE, GET, RM, LS, STOP) ----------
void* handle_client(void* arg) {
    int client_sock = *(int*)arg;
    free(arg);

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    ssize_t n = recv(client_sock, buffer, sizeof(buffer)-1, 0);
    if (n <= 0) { close(client_sock); return NULL; }
    buffer[n] = '\0';
    printf("[SERVER] Received: %s\n", buffer);

    // ---- STOP command ----
    if (strncmp(buffer, STOP_CMD, 4) == 0) {
        printf("[SERVER] STOP command received, shutting down server...\n");
        send(client_sock, "Server stopping...\n", 19, 0);
        close(client_sock);
        exit(0);
    }

    char command[16], arg1[256], arg2[256], arg3[256];
    int num_args = sscanf(buffer, "%s %s %s %s", command, arg1, arg2, arg3);

    // Ensure ROOT_DIR exists
    struct stat st = {0};
    if (stat(ROOT_DIR, &st) == -1) mkdir(ROOT_DIR, 0777);

    if (strcmp(command, "WRITE") == 0) {
        char *remote_file = (num_args >= 3) ? arg2 : arg1;
        char server_path[SERVER_PATH_SIZE];
        snprintf(server_path, sizeof(server_path), "%s/%s", ROOT_DIR, remote_file);

        // Versioning: rename existing file if it exists
        struct stat stfile;
        if (stat(server_path, &stfile) == 0) {
            char versioned_path[SERVER_PATH_SIZE];
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            snprintf(versioned_path, sizeof(versioned_path), "%s/%s.%04d%02d%02d%02d%02d%02d",
                     ROOT_DIR, remote_file,
                     tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
                     tm.tm_hour, tm.tm_min, tm.tm_sec);
            rename(server_path, versioned_path);
        }

        if (!check_disk_space(ROOT_DIR, MIN_FREE_SPACE)) {
            send(client_sock, "ERROR: Out of storage\n", 22, 0);
            close(client_sock);
            return NULL;
        }

        int fd = open(server_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd < 0) { send(client_sock, "Failed to open file", 19, 0); close(client_sock); return NULL; }
        lock_file(fd);

        FILE* fp = fdopen(fd, "wb");
        send(client_sock, "READY", 5, 0);

        ssize_t r;
        while ((r = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
            fwrite(buffer, 1, r, fp);
            if (r < sizeof(buffer)) break;
        }
        fflush(fp); unlock_file(fd); fclose(fp);
        printf("[SERVER] File saved: %s\n", server_path);

    } else if (strcmp(command, "GET") == 0) {
        char *remote_file = arg1;
        char *version = (num_args >= 4) ? arg2 : NULL;

        char server_path[SERVER_PATH_SIZE];
        if (version)
            snprintf(server_path, sizeof(server_path), "%s/%s.%s", ROOT_DIR, remote_file, version);
        else
            snprintf(server_path, sizeof(server_path), "%s/%s", ROOT_DIR, remote_file);

        FILE* fp = fopen(server_path, "rb");
        if (!fp) { send(client_sock, "File not found", 14, 0); close(client_sock); return NULL; }

        send(client_sock, "READY", 5, 0);
        size_t r;
        while ((r = fread(buffer,1,sizeof(buffer),fp))>0)
            send(client_sock, buffer, r, 0);
        fclose(fp);
        printf("[SERVER] Sent file: %s\n", server_path);

    } else if (strcmp(command, "RM") == 0) {
        char server_path[SERVER_PATH_SIZE];
        snprintf(server_path, sizeof(server_path), "%s/%s", ROOT_DIR, arg1);

        pthread_mutex_lock(&global_mutex);
        int status = remove(server_path);
        pthread_mutex_unlock(&global_mutex);

        send(client_sock, status==0?"SUCCESS":"FAIL", status==0?7:4, 0);
        printf("[SERVER] %s file %s\n", status==0?"Deleted":"Failed to delete", server_path);

    } else if (strcmp(command, "LS") == 0) {
        char *remote_file = arg1;
        DIR *d = opendir(ROOT_DIR);
        if (!d) { send(client_sock,"Error opening directory",23,0); close(client_sock); return NULL; }

        struct dirent *dir;
        char version_list[BUFFER_SIZE]; version_list[0]='\0';
        while ((dir = readdir(d)) != NULL) {
            if (strncmp(dir->d_name, remote_file, strlen(remote_file))==0 &&
                (dir->d_name[strlen(remote_file)]=='.' || dir->d_name[strlen(remote_file)]=='\0')) {
                strcat(version_list, dir->d_name);
                strcat(version_list, "\n");
            }
        }
        closedir(d);
        send(client_sock, version_list, strlen(version_list), 0);

    } else {
        send(client_sock, "Unknown command",15,0);
    }

    close(client_sock);
    return NULL;
}

// ---------- Server entry point: creates socket, listens, dispatches threads ----------
int main() {
    signal(SIGINT, handle_sigint);

    struct sockaddr_in server_addr, client_addr;
    socklen_t client_size = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    printf("[SERVER] Listening on port %d...\n", PORT);

    while (1) {
        int client_sock = accept(server_socket, (struct sockaddr*)&client_addr, &client_size);
        int* p = malloc(sizeof(int)); *p = client_sock;

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, p);
        pthread_detach(tid);
    }

    close(server_socket);
    pthread_mutex_destroy(&global_mutex);
    return 0;
}
