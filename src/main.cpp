#include "../include/dungeon_editor.h"
#include "../include/observer/console_observer.h"
#include "../include/observer/file_observer.h"
#include <iostream>

int main() {
    std::cout << "=== Dungeon Editor for Balagur Fate 3 ===\n" << std::endl;
    
    try {
        DungeonEditor editor;
        
        // Add observers
        auto consoleObserver = std::make_shared<ConsoleObserver>();
        auto fileObserver = std::make_shared<FileObserver>();
        
        editor.addObserver(consoleObserver);
        editor.addObserver(fileObserver);
        
        // Create some NPCs
        std::cout << "Creating NPCs..." << std::endl;
        editor.addNPC(NpcType::Orc, 100, 200, "Grom");
        editor.addNPC(NpcType::Squirrel, 150, 250, "Chip");
        editor.addNPC(NpcType::Druid, 200, 300, "Malfurion");
        editor.addNPC(NpcType::Orc, 250, 350, "Thrall");
        editor.addNPC(NpcType::Druid, 300, 400, "Cenarius");
        
        // Print all NPCs
        std::cout << "\n=== All NPCs ===" << std::endl;
        editor.printAll();
        
        // Save to file
        std::cout << "\nSaving to file..." << std::endl;
        editor.saveToFile("dungeon.txt");
        
        // Battle
        std::cout << "\n=== Starting Battle (range: 500) ===" << std::endl;
        editor.battle(500);
        
        // Print survivors
        std::cout << "\n=== Survivors ===" << std::endl;
        editor.printAll();
        
        // Load from file
        std::cout << "\n=== Loading from file ===" << std::endl;
        DungeonEditor editor2;
        editor2.addObserver(consoleObserver);
        editor2.loadFromFile("dungeon.txt");
        editor2.printAll();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}