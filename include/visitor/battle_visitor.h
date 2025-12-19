#pragma once


#include <memory>

class Orc;
class Squirrel;
class Druid;

class BattleVisitor {
public:
    virtual ~BattleVisitor() = default;
    virtual bool visit(const std::shared_ptr<Orc>& orc) = 0;
    virtual bool visit(const std::shared_ptr<Squirrel>& squirrel) = 0;
    virtual bool visit(const std::shared_ptr<Druid>& druid) = 0;
};

class OrcVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
};

class SquirrelVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
};

class DruidVisitor : public BattleVisitor {
public:
    bool visit(const std::shared_ptr<Orc>& orc) override;
    bool visit(const std::shared_ptr<Squirrel>& squirrel) override;
    bool visit(const std::shared_ptr<Druid>& druid) override;
};