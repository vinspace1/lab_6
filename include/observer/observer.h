#pragma once


#include <memory>
#include <string>

class NPC;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onFight(
        const std::shared_ptr<NPC>& attacker, 
        const std::shared_ptr<NPC>& defender,
        bool defender_killed
    ) = 0;
};