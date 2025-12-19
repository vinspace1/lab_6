#include <gtest/gtest.h>
#include "../include/npc/orc.h"
#include "../include/npc/squirrel.h"
#include "../include/npc/druid.h"
#include "../include/visitor/battle_visitor.h"
#include "../include/factory/npc_factory.h"

TEST(NPCTest, Creation) {
    auto orc = std::make_shared<Orc>(100, 200, "Grom");
    EXPECT_EQ(orc->getType(), NpcType::Orc);
    EXPECT_EQ(orc->getName(), "Grom");
    EXPECT_EQ(orc->getX(), 100);
    EXPECT_EQ(orc->getY(), 200);
    EXPECT_TRUE(orc->isAlive());
    
    auto squirrel = std::make_shared<Squirrel>(50, 150, "Chip");
    EXPECT_EQ(squirrel->getType(), NpcType::Squirrel);
    
    auto druid = std::make_shared<Druid>(200, 300, "Malfurion");
    EXPECT_EQ(druid->getType(), NpcType::Druid);
}

TEST(NPCTest, Distance) {
    auto npc1 = std::make_shared<Orc>(0, 0, "Grom");
    auto npc2 = std::make_shared<Squirrel>(3, 4, "Chip");
    
    EXPECT_DOUBLE_EQ(npc1->distanceTo(npc2), 5.0);
}

TEST(BattleTest, OrcVsDruid) {
    auto orc = std::make_shared<Orc>(0, 0, "Grom");
    auto druid = std::make_shared<Druid>(1, 0, "Malfurion");
    auto visitor = std::make_shared<OrcVisitor>();
    
    EXPECT_TRUE(druid->isAlive());
    bool killed = druid->accept(visitor);
    EXPECT_TRUE(killed);
    EXPECT_FALSE(druid->isAlive());
}

TEST(BattleTest, DruidVsSquirrel) {
    auto druid = std::make_shared<Druid>(0, 0, "Malfurion");
    auto squirrel = std::make_shared<Squirrel>(1, 0, "Chip");
    auto visitor = std::make_shared<DruidVisitor>();
    
    EXPECT_TRUE(squirrel->isAlive());
    bool killed = squirrel->accept(visitor);
    EXPECT_TRUE(killed);
    EXPECT_FALSE(squirrel->isAlive());
}

TEST(BattleTest, SquirrelIsPeaceful) {
    auto squirrel = std::make_shared<Squirrel>(0, 0, "Chip");
    auto orc = std::make_shared<Orc>(1, 0, "Grom");
    auto visitor = std::make_shared<SquirrelVisitor>();
    
    EXPECT_TRUE(orc->isAlive());
    bool killed = orc->accept(visitor);
    EXPECT_FALSE(killed);
    EXPECT_TRUE(orc->isAlive());
}

TEST(FactoryTest, CreateNPC) {
    auto orc = NPCFactory::createNPC(NpcType::Orc, 10, 20, "Grom");
    EXPECT_EQ(orc->getType(), NpcType::Orc);
    
    auto squirrel = NPCFactory::createNPC(NpcType::Squirrel, 30, 40, "Chip");
    EXPECT_EQ(squirrel->getType(), NpcType::Squirrel);
    
    auto druid = NPCFactory::createNPC(NpcType::Druid, 50, 60, "Malfurion");
    EXPECT_EQ(druid->getType(), NpcType::Druid);
}

TEST(FactoryTest, SerializeDeserialize) {
    auto orc = std::make_shared<Orc>(100, 200, "Grom Hellscream");
    std::string data = NPCFactory::serializeNPC(orc);
    
    EXPECT_EQ(data, "Orc 100 200 Grom Hellscream");
    
    auto loaded = NPCFactory::createNPCFromString(data);
    EXPECT_EQ(loaded->getType(), NpcType::Orc);
    EXPECT_EQ(loaded->getX(), 100);
    EXPECT_EQ(loaded->getY(), 200);
    EXPECT_EQ(loaded->getName(), "Grom Hellscream");
}