#pragma once


#include "observer.h"
#include <memory>
#include <fstream>

class FileObserver : public Observer {
private:
    std::ofstream logFile;
    
public:
    FileObserver(const std::string& filename = "log.txt");
    ~FileObserver();
    
    void onFight(
        const std::shared_ptr<NPC>& attacker, 
        const std::shared_ptr<NPC>& defender,
        bool defender_killed
    ) override;
};