#include "../../include/npc/squirrel.h"
#include "../../include/visitor/battle_visitor.h"
#include <memory>

Squirrel::Squirrel(int x, int y, const std::string& name) 
    : NPC(x, y, name, NpcType::Squirrel) {
}

bool Squirrel::accept(const std::shared_ptr<BattleVisitor>& attacker) {
    return attacker->visit(std::dynamic_pointer_cast<Squirrel>(shared_from_this()));
}

std::string Squirrel::getTypeName() const {
    return "Squirrel";
}