#pragma once


#include <vector>
#include <memory>
#include <string>
#include "npc/npc.h"
#include "observer/observer.h"

class DungeonEditor {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;
    
    bool isPositionValid(int x, int y) const;
    
public:
    DungeonEditor();
    
    void addNPC(NpcType type, int x, int y, const std::string& name);
    bool removeNPC(const std::string& name);
    
    void printAll() const;
    size_t count() const { return npcs.size(); }
    
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    void addObserver(const std::shared_ptr<Observer>& observer);
    void removeObserver(const std::shared_ptr<Observer>& observer);
    
    void battle(int range);
    
    void notifyObservers(
        const std::shared_ptr<NPC>& attacker,
        const std::shared_ptr<NPC>& defender,
        bool defender_killed
    ) const;
    
    void clear();
    void removeDeadNPCs();
    
    const std::vector<std::shared_ptr<NPC>>& getNPCs() const { return npcs; }
};