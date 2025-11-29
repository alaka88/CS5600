#!/bin/bash
# test_rfs.sh - Full automated test for RFS assignment with explicit logging
# Zhimin Wang

SERVER_SRC=server.c
CLIENT_SRC=client.c
SERVER_EXEC=./server
CLIENT_EXEC=./client
ROOT_DIR=server_files

echo "=== RFS Automated Test ==="

# --- Step 0: Compile server and client ---
if [ ! -f "$SERVER_EXEC" ]; then
    gcc -o server "$SERVER_SRC" -lpthread || { echo "Server compilation failed"; exit 1; }
fi
if [ ! -f "$CLIENT_EXEC" ]; then
    gcc -o client "$CLIENT_SRC" || { echo "Client compilation failed"; exit 1; }
fi

# --- Step 1: Prepare server root folder ---
mkdir -p $ROOT_DIR
echo "[TEST] Server root folder prepared: $ROOT_DIR"

# --- Step 2: Start server in background ---
$SERVER_EXEC &
SERVER_PID=$!
echo "[TEST] Server started with PID $SERVER_PID"
sleep 1

# --- Step 3: Prepare test files ---
echo "hello assignment test" > test_local.txt
echo "Client1 test data" > client1.txt
echo "Client2 test data" > client2.txt
echo "Version 1" > version.txt
echo "[TEST] Test files prepared"

# --- Step 4: Upload a single file (WRITE) ---
echo "[TEST] Uploading test_local.txt as uploaded.txt"
$CLIENT_EXEC WRITE test_local.txt uploaded.txt

# --- Step 5: Verify the file on server ---
if [[ -f "$ROOT_DIR/uploaded.txt" ]]; then
    echo "[TEST] Server file exists: uploaded.txt"
    cat $ROOT_DIR/uploaded.txt
else
    echo "[ERROR] uploaded.txt not found on server!"
fi

# --- Step 6: Download the file back (GET) ---
echo "[TEST] Downloading uploaded.txt as downloaded.txt"
$CLIENT_EXEC GET uploaded.txt downloaded.txt
if diff test_local.txt downloaded.txt >/dev/null; then
    echo "[TEST] Downloaded file matches original"
else
    echo "[ERROR] Downloaded file mismatch"
fi

# --- Step 7: Test concurrent writes ---
echo "[TEST] Concurrent writes to shared.txt"
$CLIENT_EXEC WRITE client1.txt shared.txt &
PID1=$!
$CLIENT_EXEC WRITE client2.txt shared.txt &
PID2=$!
wait $PID1 $PID2
echo "[TEST] Final content of shared.txt:"
cat $ROOT_DIR/shared.txt

# --- Step 8: Test concurrent GET ---
$CLIENT_EXEC GET shared.txt client1_copy.txt &
PID1=$!
$CLIENT_EXEC GET shared.txt client2_copy.txt &
PID2=$!
wait $PID1 $PID2
echo "[TEST] Concurrent GET completed"

# --- Step 9: Test RM command ---
echo "[TEST] Removing shared.txt"
$CLIENT_EXEC RM shared.txt
sleep 1
if [[ ! -f "$ROOT_DIR/shared.txt" ]]; then
    echo "[TEST] shared.txt successfully deleted"
else
    echo "[ERROR] shared.txt not deleted"
fi

# --- Step 10: Test versioning ---
echo "[TEST] Writing multiple versions to shared.txt"
echo "Version 1" > version.txt
$CLIENT_EXEC WRITE version.txt shared.txt
sleep 1
echo "Version 2" > version.txt
$CLIENT_EXEC WRITE version.txt shared.txt
sleep 1

# --- Step 11: List all versions (LS) ---
echo "[TEST] Listing all versions of shared.txt"
$CLIENT_EXEC LS shared.txt

# --- Step 12 & 13: Download first version ---
VERSION_FILES=($(ls $ROOT_DIR/shared.txt.* 2>/dev/null | sort))
if [ ${#VERSION_FILES[@]} -eq 0 ]; then
    echo "[ERROR] No versioned files found"
else
    FIRST_VERSION=$(basename ${VERSION_FILES[0]} | awk -F'shared.txt.' '{print $2}')
    echo "[TEST] Downloading first version ($FIRST_VERSION) as local_v1.txt"
    $CLIENT_EXEC GET shared.txt $FIRST_VERSION local_v1.txt
    echo "[TEST] Content of local_v1.txt:"
    cat local_v1.txt
fi

# --- Step 14: Download latest version ---
echo "[TEST] Downloading latest version as local_v2.txt"
$CLIENT_EXEC GET shared.txt local_v2.txt
echo "[TEST] Content of local_v2.txt:"
cat local_v2.txt

# --- Step 15: Stop the server ---
echo "[TEST] Sending STOP command to server"
$CLIENT_EXEC STOP &
STOP_PID=$!
wait $STOP_PID

sleep 1
if ps -p $SERVER_PID >/dev/null; then
    echo "[ERROR] Server did not stop automatically, killing..."
    kill $SERVER_PID
    wait $SERVER_PID 2>/dev/null
else
    echo "[TEST] Server stopped successfully"
fi

echo "=== RFS Automated Test Completed ==="
