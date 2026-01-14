#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <chrono>

std::mutex mtx;
std::map<std::string, int> logCount;

// Function to process logs
void processLogs() {
    std::ifstream logFile("app.log");
    std::ofstream errorFile("error.log", std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Failed to open app.log\n";
        return;
    }

    std::string line;
    while (std::getline(logFile, line)) {
        std::lock_guard<std::mutex> lock(mtx);

        if (line.find("INFO") != std::string::npos) {
            logCount["INFO"]++;
        } 
        else if (line.find("ERROR") != std::string::npos) {
            logCount["ERROR"]++;
            errorFile << line << std::endl;
        } 
        else if (line.find("WARN") != std::string::npos) {
            logCount["WARN"]++;
        } 
        else {
            logCount["OTHER"]++;
        }
    }

    logFile.close();
    errorFile.close();
}

// Function to print summary every 10 seconds
void printSummary() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));

        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "\n===== Log Summary =====\n";
        for (auto &entry : logCount) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
        std::cout << "=======================\n";
    }
}

int main() {
    std::cout << "Log Server Started...\n";

    std::thread logThread(processLogs);
    std::thread summaryThread(printSummary);

    logThread.join();
    summaryThread.join();

    return 0;
}
