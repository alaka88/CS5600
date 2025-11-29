Course: CS5600 Practicum II
Assignment: Remote File System (RFS)
Author: Zhimin Wang
Date: 11/29/2025

--------------------------------------------------
1. Design Overview
--------------------------------------------------

This project implements a multi-threaded TCP-based Remote File System (RFS) with the following features:

- WRITE: Upload a local file from the client to the server. 
  - Supports file versioning: if the remote file already exists, it is saved with a timestamp before being overwritten.
  - Uses file locks to prevent corruption when multiple clients write to the same file concurrently.

- GET: Download a file from the server to the client.
  - Can request the latest version or a specific version of a file.
  
- RM: Delete a file from the server.
  
- LS: List all versions of a file stored on the server.

- Concurrency: 
  - The server is multi-threaded.
  - Each client connection is handled by a separate thread.
  - Critical sections (file access and deletion) are protected using mutexes and file locks.

- Safe Exit: 
  - Server catches SIGINT (Ctrl-C) to perform a graceful shutdown.

- Storage Check: 
  - Server checks available disk space before accepting new file uploads and returns an error if insufficient.

--------------------------------------------------
2. Directory Structure
--------------------------------------------------

Project files:
.
├── server.c           # Server implementation
├── client.c           # Client implementation
├── utils.c            # Utility functions (locks, disk checks)
├── rfs.h              # Shared header
├── test_rfs.sh        # Automated test script
├── Makefile           # Build automation
└── README.txt          # This file

--------------------------------------------------
3. Automated Testing
--------------------------------------------------
A Makefile is provided to simplify compilation and testing.
1) Compile Server and Client:
'''bash
make

Produces two executables:
server
client

2) Automated Test:
'''bash
make test

Runs test_rfs.sh which automatically:
Starts the server
Creates test files
Uploads, downloads, and deletes files
Tests concurrency and versioning
Stops the server at the end

3) Clean:
'''bash
make clean

Removes executables, temporary files, and server root folder.




--------------------------------------------------
4. Manually Compilation Instructions(optional)
--------------------------------------------------

In the project directory, run:

```bash
gcc -o server server.c -lpthread
gcc -o client client.c

This will produce two executables:
server
client

5. How to Run the Server

Before starting the server, create the root folder:
mkdir -p server_files

Start the server:
./server

Expected output:
- Server listens on port 2000 (default) and waits for clients.
- Server prints connection messages and received commands.
- Server continues running until manually stopped (Ctrl-C).

6. How to Run the Client
Prepare a test file:
echo "hello assignment test" > test_local.txt

Run the client:
./client WRITE test_local.txt uploaded.txt

Expected output:
Connected to server.
Server is READY. Sending file...
File 'test_local.txt' uploaded as 'uploaded.txt'

7. Verify the File on the Server
After running the client, check the server directory:
ls -l server_files

View the uploaded file:
cat server_files/uploaded.txt

Expected output:hello assignment test

The server should print:
Client connected: <IP>:<PORT>
Received from client: WRITE test_local.txt uploaded.txt
File saved to: server_files/uploaded.txt

8.Download the file from server
./client GET uploaded.txt downloaded.txt
cat downloaded.txt        # verify file content

Expected output:hello assignment

9.Delete a file (RM)
./client RM uploaded.txt

Expect output:RM_SUCCESS

10.Create two test files for client simulations

echo "Client1 test data" > client1.txt
echo "Client2 test data" > client2.txt

Open Multiple Client Terminals
Terminal 1 (Client 1):

./client WRITE client1.txt shared.txt

Terminal 2 (Client 2):

gcc -o client client.c
./client WRITE client2.txt shared.txt

Note: Both clients write to the same file shared.txt on the server to test concurrency and file integrity.

11.Verify File Integrity
On the server terminal, check the contents of shared.txt:
cat server_files/shared.txt

12.Test Other Operations Concurrently
GET command:

./client GET shared.txt client1_copy.txt
./client GET shared.txt client2_copy.txt

RM command
./client RM shared.txt

13.File Versioning
a.Prepare the local file for the first version:
echo "Version 1" > version.txt
./client WRITE version.txt shared.txt

b.echo "Version 2" > version.txt
./client WRITE version.txt shared.txt

Expected Behavior:
The server keeps the previous version as a timestamped backup, eg:
server_files/shared.txt.yyyymmddhhmmss   # previous version
server_files/shared.txt                   # latest version

14.Viewing All Versions of a File
./client LS shared.txt

Example Output:
Versions of 'shared.txt':
shared.txt.20251127002750
shared.txt.20251127002827
shared.txt.20251127002902

15.Downloading a Specific Version of a File
Suppose you want to download the first version: shared.txt.20251127002750:
./client GET shared.txt 20251127002750 local_v1.txt

Note:
- The server assumes the root folder exists or creates it at startup.
- Clients and server must be run on the same machine for testing, but TCP allows different machines.
- File names with spaces are not supported.
- Disk space is checked, but fragmentation is ignored.
- SIGINT handler ensures graceful shutdown.

