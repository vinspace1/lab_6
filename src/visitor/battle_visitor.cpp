#include "../../include/visitor/battle_visitor.h"
#include "../../include/npc/orc.h"
#include "../../include/npc/squirrel.h"
#include "../../include/npc/druid.h"

// OrcVisitor
bool OrcVisitor::visit(const std::shared_ptr<Orc>& orc) {
    // Орки не дерутся с орками
    return false;
}

bool OrcVisitor::visit(const std::shared_ptr<Squirrel>& squirrel) {
    // Белки за мир, орки их не трогают
    return false;
}

bool OrcVisitor::visit(const std::shared_ptr<Druid>& druid) {
    // Орки убивают друидов
    druid->kill();
    return true;
}

// SquirrelVisitor
bool SquirrelVisitor::visit(const std::shared_ptr<Orc>& orc) {
    // Белки за мир
    return false;
}

bool SquirrelVisitor::visit(const std::shared_ptr<Squirrel>& squirrel) {
    // Белки не дерутся друг с другом
    return false;
}

bool SquirrelVisitor::visit(const std::shared_ptr<Druid>& druid) {
    // Белки за мир, даже против друидов
    return false;
}

// DruidVisitor
bool DruidVisitor::visit(const std::shared_ptr<Orc>& orc) {
    // Друиды не могут убить орков
    return false;
}

bool DruidVisitor::visit(const std::shared_ptr<Squirrel>& squirrel) {
    // Друиды убивают белок
    squirrel->kill();
    return true;
}

bool DruidVisitor::visit(const std::shared_ptr<Druid>& druid) {
    // Друиды не дерутся с друидами
    return false;
}