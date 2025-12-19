#include "../include/dungeon_editor.h"
#include "../include/factory/npc_factory.h"
#include "../include/visitor/battle_visitor.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <string>

DungeonEditor::DungeonEditor() {}

bool DungeonEditor::isPositionValid(int x, int y) const {
    return x >= 0 && x <= 500 && y >= 0 && y <= 500;
}

void DungeonEditor::addNPC(NpcType type, int x, int y, const std::string& name) {
    if (!isPositionValid(x, y)) {
        std::string error = "Position (" + std::to_string(x) + ", " + 
                           std::to_string(y) + ") is out of bounds";
        throw std::invalid_argument(error);
    }
    
    auto npc = NPCFactory::createNPC(type, x, y, name);
    npcs.push_back(npc);
    std::cout << "Added " << npc->toString() << std::endl;
}


void DungeonEditor::printAll() const {
    std::cout << "\n=== Dungeon NPCs (" + std::to_string(npcs.size()) + ") ===" << std::endl;
    for (const auto& npc : npcs) {
        std::cout << "- " << npc->toString();
        if (!npc->isAlive()) {
            std::cout << " [DEAD]";
        }
        std::cout << std::endl;
    }
    std::cout << "=====================\n" << std::endl;
}

void DungeonEditor::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    for (const auto& npc : npcs) {
        file << NPCFactory::serializeNPC(npc) << std::endl;
    }
    
    file.close();
    std::cout << "Saved " + std::to_string(npcs.size()) + " NPCs to " + filename << std::endl;
}

void DungeonEditor::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    npcs.clear();
    std::string line;
    int count = 0;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                auto npc = NPCFactory::createNPCFromString(line);
                npcs.push_back(npc);
                count++;
            } catch (const std::exception& e) {
                std::cerr << "Error loading NPC: " << e.what() << std::endl;
            }
        }
    }
    
    file.close();
    std::cout << "Loaded " + std::to_string(count) + " NPCs from " + filename << std::endl;
}

void DungeonEditor::battle(int range) {
    std::cout << "\n=== BATTLE START (range: " + std::to_string(range) + ") ===" << std::endl;
    
    // Векторы для хранения, кто кого убивает
    std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> killings;
    
    // Проходим по всем парам NPC
    for (size_t i = 0; i < npcs.size(); i++) {
        auto& attacker = npcs[i];
        if (!attacker->isAlive()) continue;
        
        for (size_t j = i + 1; j < npcs.size(); j++) {
            auto& defender = npcs[j];
            if (!defender->isAlive()) continue;
            
            // Проверяем дальность
            if (attacker->distanceTo(defender) > range) continue;
            
            // Атака attacker -> defender
            if (attacker->getType() == NpcType::Orc && defender->getType() == NpcType::Druid) {
                killings.emplace_back(attacker, defender);
            }
            if (attacker->getType() == NpcType::Druid && defender->getType() == NpcType::Squirrel) {
                killings.emplace_back(attacker, defender);
            }
            
            // Атака defender -> attacker (обратная)
            if (defender->getType() == NpcType::Orc && attacker->getType() == NpcType::Druid) {
                killings.emplace_back(defender, attacker);
            }
            if (defender->getType() == NpcType::Druid && attacker->getType() == NpcType::Squirrel) {
                killings.emplace_back(defender, attacker);
            }
        }
    }
    
    // Применяем убийства
    for (const auto& [killer, victim] : killings) {
        if (victim->isAlive()) {
            victim->kill();
            notifyObservers(killer, victim, true);
        }
    }
    
    removeDeadNPCs();
    std::cout << "=== BATTLE END ===" << std::endl;
}

bool DungeonEditor::removeNPC(const std::string& name) {
    auto it = std::remove_if(npcs.begin(), npcs.end(),
        [&name](const std::shared_ptr<NPC>& npc) {
            return npc->getName() == name;
        });
    
    if (it != npcs.end()) {
        npcs.erase(it, npcs.end());
        return true;
    }
    return false;
}

void DungeonEditor::addObserver(const std::shared_ptr<Observer>& observer) {
    observers.push_back(observer);
}

void DungeonEditor::removeObserver(const std::shared_ptr<Observer>& observer) {
    auto it = std::remove(observers.begin(), observers.end(), observer);
    observers.erase(it, observers.end());
}

void DungeonEditor::notifyObservers(
    const std::shared_ptr<NPC>& attacker,
    const std::shared_ptr<NPC>& defender,
    bool defender_killed
) const {
    for (const auto& observer : observers) {
        observer->onFight(attacker, defender, defender_killed);
    }
}

void DungeonEditor::removeDeadNPCs() {
    auto it = std::remove_if(npcs.begin(), npcs.end(),
        [](const std::shared_ptr<NPC>& npc) {
            return !npc->isAlive();
        });
    
    size_t removed = std::distance(it, npcs.end());
    npcs.erase(it, npcs.end());
    
    if (removed > 0) {
        std::cout << "Removed " + std::to_string(removed) + " dead NPCs" << std::endl;
    }
}

void DungeonEditor::clear() {
    npcs.clear();
    std::cout << "Dungeon cleared" << std::endl;
}