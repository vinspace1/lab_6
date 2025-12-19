#include "../../include/observer/console_observer.h"
#include "../../include/npc/npc.h"
#include <iostream>

void ConsoleObserver::onFight(
    const std::shared_ptr<NPC>& attacker, 
    const std::shared_ptr<NPC>& defender,
    bool defender_killed
) {
    std::cout << attacker->getTypeName() + " '" + attacker->getName() +
                 "' attacks " + defender->getTypeName() + " '" + 
                 defender->getName() + "'";
    
    if (defender_killed) {
        std::cout << " and kills it!";
    } else {
        std::cout << " but fails to kill it.";
    }
    
    std::cout << std::endl;
}