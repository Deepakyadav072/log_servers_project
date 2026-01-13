#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

std::mutex mtx;
std::map<std::string, int> summary;

// Thread 1: Read log file and prepare summary
void readLogFile() {
    std::ifstream file("app.log");
    std::string line;

    if (!file.is_open()) return;

    while (getline(file, line)) {
        std::lock_guard<std::mutex> lock(mtx);

        summary["TOTAL"]++;

        if (line.find("ERROR") != std::string::npos)
            summary["ERROR"]++;
        else if (line.find("WARNING") != std::string::npos)
            summary["WARNING"]++;
        else
            summary["INFO"]++;
    }
}

// Thread 2: TCP server sends summary to client
void startServer() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 1);

    int clientSocket = accept(serverSocket, nullptr, nullptr);

    std::lock_guard<std::mutex> lock(mtx);

    std::string message =
        "Total Lines: " + std::to_string(summary["TOTAL"]) + "\n" +
        "ERROR: " + std::to_string(summary["ERROR"]) + "\n" +
        "WARNING: " + std::to_string(summary["WARNING"]) + "\n" +
        "INFO: " + std::to_string(summary["INFO"]) + "\n";

    send(clientSocket, message.c_str(), message.size(), 0);

    close(clientSocket);
    close(serverSocket);
}

int main() {
    std::thread t1(readLogFile);
    std::thread t2(startServer);

    t1.join();
    t2.join();

    return 0;
}
