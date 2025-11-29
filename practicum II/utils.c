// Zhimin Wang
// 11/28/2025

#include "rfs.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

extern int server_socket;

// Called when client sends STOP
void handle_stop_request() {
    printf("[SERVER] STOP command received. Shutting down server...\n");
    close(server_socket);
    kill(getpid(), SIGINT);  // trigger the signal handler
}
