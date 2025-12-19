#include "../../include/npc/npc.h"
#include <cmath>
#include <string>

NPC::NPC(int x, int y, const std::string& name, NpcType type) 
    : x(x), y(y), name(name), type(type), alive(true) {
}

double NPC::distanceTo(const std::shared_ptr<NPC>& other) const {
    int dx = x - other->getX();
    int dy = y - other->getY();
    return std::sqrt(dx*dx + dy*dy);
}

std::string NPC::toString() const {
    std::string result = getTypeName() + " '" + name + "' at (" + 
                        std::to_string(x) + ", " + std::to_string(y) + ")";
    return result;
}