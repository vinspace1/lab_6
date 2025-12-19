#include <gtest/gtest.h>
#include "../include/dungeon_editor.h"
#include "../include/observer/console_observer.h"
#include "../include/observer/file_observer.h"

TEST(DungeonEditorTest, AddAndRemove) {
    DungeonEditor editor;
    
    EXPECT_EQ(editor.count(), 0);
    
    editor.addNPC(NpcType::Orc, 100, 100, "Grom");
    EXPECT_EQ(editor.count(), 1);
    
    editor.addNPC(NpcType::Squirrel, 200, 200, "Chip");
    EXPECT_EQ(editor.count(), 2);
    
    bool removed = editor.removeNPC("Grom");
    EXPECT_TRUE(removed);
    EXPECT_EQ(editor.count(), 1);
    
    removed = editor.removeNPC("NonExistent");
    EXPECT_FALSE(removed);
    EXPECT_EQ(editor.count(), 1);
}

TEST(DungeonEditorTest, InvalidPosition) {
    DungeonEditor editor;
    
    EXPECT_THROW(editor.addNPC(NpcType::Orc, 600, 100, "Grom"), 
                 std::invalid_argument);
    EXPECT_THROW(editor.addNPC(NpcType::Orc, 100, 600, "Grom"), 
                 std::invalid_argument);
    EXPECT_THROW(editor.addNPC(NpcType::Orc, -10, 100, "Grom"), 
                 std::invalid_argument);
}

TEST(DungeonEditorTest, BattleScenario) {
    DungeonEditor editor;
    
    // Добавляем наблюдателя
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    editor.addObserver(consoleObserver);
    
    // Создаем NPC для боя
    editor.addNPC(NpcType::Orc, 0, 0, "Grom");
    editor.addNPC(NpcType::Druid, 1, 0, "Malfurion");
    editor.addNPC(NpcType::Squirrel, 2, 0, "Chip");
    editor.addNPC(NpcType::Druid, 3, 0, "Cenarius");
    
    EXPECT_EQ(editor.count(), 4);
    
    // Запускаем бой с дальностью 10 (все в радиусе)
    editor.battle(10);
    
    // Орк атакует обоих друидов -> оба друида умирают
    // Друиды атакуют белку -> белка умирает (друиды атакуют, даже если их убивают)
    // Белка никого не атакует (она мирная)
    
    // Результат: орк убивает обоих друидов, друиды убивают белку
    // Должен остаться только орк
    EXPECT_EQ(editor.count(), 1);
    
    // Проверяем, что выжил именно орк
    auto survivors = editor.getNPCs();
    ASSERT_EQ(survivors.size(), 1);
    EXPECT_EQ(survivors[0]->getType(), NpcType::Orc);
    EXPECT_EQ(survivors[0]->getName(), "Grom");
    
    editor.clear();
}

TEST(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor;
    
    editor.addNPC(NpcType::Orc, 100, 100, "Grom");
    editor.addNPC(NpcType::Squirrel, 200, 200, "Chip");
    editor.addNPC(NpcType::Druid, 300, 300, "Malfurion");
    
    const std::string filename = "test_save.txt";
    editor.saveToFile(filename);
    
    DungeonEditor editor2;
    editor2.loadFromFile(filename);
    
    EXPECT_EQ(editor2.count(), 3);
    
    std::remove(filename.c_str());
}