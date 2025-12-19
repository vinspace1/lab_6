#include "../../include/npc/druid.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Druid::Druid(int x, int y, const std::string& name) 
    : NPC(x, y, name, NpcType::Druid) {
}

bool Druid::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::dynamic_pointer_cast<Druid>(shared_from_this()));
}

std::string Druid::getTypeName() const {
    return "Druid";
}