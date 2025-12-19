#pragma once


#include <string>
#include <memory>

enum class NpcType {
    Orc,
    Squirrel,
    Druid
};

class BattleVisitor;

class NPC : public std::enable_shared_from_this<NPC> {
protected:
    int x;
    int y;
    std::string name;
    NpcType type;
    bool alive;

public:
    NPC(int x, int y, const std::string& name, NpcType type);
    virtual ~NPC() = default;

    virtual bool accept(const std::shared_ptr<BattleVisitor>& attacker) = 0;
    
    int getX() const { return x; }
    int getY() const { return y; }
    std::string getName() const { return name; }
    NpcType getType() const { return type; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }
    
    virtual std::string getTypeName() const = 0;
    double distanceTo(const std::shared_ptr<NPC>& other) const;
    
    virtual std::string toString() const;
};