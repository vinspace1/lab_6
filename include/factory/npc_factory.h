#pragma once


#include <memory>
#include <string>
#include "../npc/npc.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(
        NpcType type, 
        int x, 
        int y, 
        const std::string& name
    );
    
    static std::shared_ptr<NPC> createNPCFromString(const std::string& data);
    static std::string serializeNPC(const std::shared_ptr<NPC>& npc);
};