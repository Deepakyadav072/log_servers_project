
# Log Server Project (C++)

## 📌 Project Overview
This project is a simple *Log Server Application* written in *C++*.  
It reads logs from a file, processes them in real time, and provides a summary of log types such as *INFO, **WARNING, and **ERROR*.

The project is designed for beginners and demonstrates:
- C++ STL usage
- File handling
- Multithreading
- Basic Linux commands
- Git & GitHub workflow
- Production-style thinking

---

## 🎯 Features
- ✅ Read logs from app.log
- ✅ Count logs by type (INFO, WARNING, ERROR)
- ✅ Display real-time log summary every *10 seconds*
- ✅ Write all ERROR logs into a separate file error.log
- ✅ Runs on Linux terminal
- ✅ Easy to extend (networking, Docker, CI/CD)

---

## 🏗️ Architecture
- The program continuously reads the log file.
- Logs are classified by type.
- Summary is printed every 10 seconds.
- ERROR logs are stored separately.

---

## 🧵 Thread Model
- *Main Thread*
  - Starts the application
  - Launches worker threads

- *Log Reader Thread*
  - Reads app.log
  - Updates log counters
  - Writes ERROR logs to error.log

- *Summary Thread*
  - Prints log summary every 10 seconds

This model ensures:
- Non-blocking execution
- Better performance
- Scalability for large log files

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
Log server started...
Reading logs from app.log

---- Log Summary ----
INFO     : 4
WARNING  : 2
ERROR    : 1
---------------------

(Updated every 10 seconds)

### Docker Setup 
Build Docker image
docker build -t log-server .

### Run Docker container

docker run -p 8080:8080 log-server

### Then connect using:
nc localhost 8080