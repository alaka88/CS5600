// rfs.h -- shared declarations for RFS client/server
// Zhimin Wamh
// 11/28/2025

#ifndef RFS_H
#define RFS_H

#define BUFFER_SIZE 8192
#define PORT 2000
#define ROOT_DIR "server_files"
#define SERVER_PATH_SIZE 1024
#define MIN_FREE_SPACE 10485760  // 10 MB

// ---- STOP command support ----
#define STOP_CMD "STOP"

void handle_stop_request();   // server shutdown (called by STOP command handler)

#endif
