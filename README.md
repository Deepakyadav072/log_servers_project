# Log Summary TCP Server (C++)

## Overview
This project is a simple C++ application that reads a log file and sends a log summary to a client using a TCP socket server.  
It is designed for beginners to demonstrate C++ fundamentals, Linux usage, networking, and basic Docker concepts.

---

## Features
- Reads a log file (app.log)
- Counts INFO, WARNING, and ERROR messages
- Uses multi-threading for log processing and networking
- Sends log summary to client via TCP
- Can be built and run on Linux
- Dockerized for easy deployment

---

## Architecture
The application has two main components:
1. *Log Processor*
   - Reads the log file line by line
   - Counts different log levels
2. *TCP Server*
   - Listens on a port (8080)
   - Sends log summary to a client when connected

Both components run in separate threads.

---

## Thread Model
- *Thread 1:* Reads and processes the log file
- *Thread 2:* Runs the TCP socket server
- A mutex is used to protect shared data (log summary)

This simple thread model keeps the code easy to understand and debug.

---

## File Structure

log_servers_project/ ├── main.cpp ├── app.log ├── Makefile ├── Dockerfile ├── README.md └── .gitignore

## How to Run (Linux)

### Step 1: Go to project directory

cd ~/log_servers_project

### Step 2: Compile the program
make

### Step 3: Run the server
./log_server
(The server will wait for a client connection)

### Step 4: Open another terminal and connect as client

nc localhost 8080

### step 5: Sample Output

Total Lines: 5
ERROR: 2
WARNING: 1
INFO: 2

### Docker Setup 
Build Docker image
docker build -t log-server .

### Run Docker container

docker run -p 8080:8080 log-server

### Then connect using:
nc localhost 8080