#pragma once


#include "observer.h"
#include <memory>

class ConsoleObserver : public Observer {
public:
    void onFight(
        const std::shared_ptr<NPC>& attacker, 
        const std::shared_ptr<NPC>& defender,
        bool defender_killed
    ) override;
};