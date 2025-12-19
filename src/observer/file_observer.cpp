#include "../../include/observer/file_observer.h"
#include "../../include/npc/npc.h"
#include <chrono>
#include <iomanip>
#include <string>

FileObserver::FileObserver(const std::string& filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Cannot open log file: " + filename);
    }
}

FileObserver::~FileObserver() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void FileObserver::onFight(
    const std::shared_ptr<NPC>& attacker, 
    const std::shared_ptr<NPC>& defender,
    bool defender_killed
) {
    if (!logFile.is_open()) return;
    
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    
    logFile << timeStr << " - ";
    logFile << attacker->getTypeName() + " '" + attacker->getName() +
               "' attacks " + defender->getTypeName() + " '" + 
               defender->getName() + "'";
    
    if (defender_killed) {
        logFile << " and kills it!";
    } else {
        logFile << " but fails to kill it.";
    }
    
    logFile << std::endl;
}