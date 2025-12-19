#include "../../include/npc/orc.h"
#include "../../include/visitor/battle_visitor.h"
#include <sstream>

Orc::Orc(int x, int y, const std::string& name) 
    : NPC(x, y, name, NpcType::Orc) {
}

bool Orc::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::dynamic_pointer_cast<Orc>(shared_from_this()));
}

std::string Orc::getTypeName() const {
    return "Orc";
}