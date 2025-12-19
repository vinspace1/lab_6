#include "../../include/factory/npc_factory.h"
#include "../../include/npc/orc.h"
#include "../../include/npc/squirrel.h"
#include "../../include/npc/druid.h"
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>

std::shared_ptr<NPC> NPCFactory::createNPC(
    NpcType type, 
    int x, 
    int y, 
    const std::string& name
) {
    switch (type) {
        case NpcType::Orc:
            return std::make_shared<Orc>(x, y, name);
        case NpcType::Squirrel:
            return std::make_shared<Squirrel>(x, y, name);
        case NpcType::Druid:
            return std::make_shared<Druid>(x, y, name);
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}

// Вспомогательная функция для обрезки пробелов
static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::shared_ptr<NPC> NPCFactory::createNPCFromString(const std::string& data) {
    std::string trimmed = trim(data);
    if (trimmed.empty()) {
        throw std::invalid_argument("Empty NPC data");
    }
    
    // Находим первый пробел (отделяет тип от координат)
    size_t firstSpace = trimmed.find(' ');
    if (firstSpace == std::string::npos) {
        throw std::invalid_argument("Invalid NPC data: missing coordinates");
    }
    
    std::string typeStr = trimmed.substr(0, firstSpace);
    
    // Находим второй пробел (отделяет X от Y)
    size_t secondSpace = trimmed.find(' ', firstSpace + 1);
    if (secondSpace == std::string::npos) {
        throw std::invalid_argument("Invalid NPC data: missing Y coordinate");
    }
    
    // Извлекаем координату X
    std::string xStr = trimmed.substr(firstSpace + 1, secondSpace - firstSpace - 1);
    
    // Находим третий пробел (отделяет Y от имени)
    size_t thirdSpace = trimmed.find(' ', secondSpace + 1);
    
    std::string yStr, name;
    
    if (thirdSpace == std::string::npos) {
        // Нет имени
        yStr = trimmed.substr(secondSpace + 1);
        name = "";
    } else {
        // Есть имя
        yStr = trimmed.substr(secondSpace + 1, thirdSpace - secondSpace - 1);
        name = trim(trimmed.substr(thirdSpace + 1));
    }
    
    // Проверяем корректность координат
    if (xStr.empty() || yStr.empty()) {
        throw std::invalid_argument("Invalid NPC data: empty coordinates");
    }
    
    // Проверяем, что координаты содержат только цифры
    auto isNumber = [](const std::string& s) {
        return !s.empty() && std::all_of(s.begin(), s.end(), 
               [](unsigned char c) { return std::isdigit(c) || c == '-'; });
    };
    
    if (!isNumber(xStr) || !isNumber(yStr)) {
        throw std::invalid_argument("Invalid NPC data: coordinates must be numbers");
    }
    
    // Преобразуем строки в числа
    int x, y;
    try {
        x = std::stoi(xStr);
        y = std::stoi(yStr);
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid NPC data: " + std::string(e.what()));
    }
    
    // Определяем тип NPC
    NpcType type;
    if (typeStr == "Orc") {
        type = NpcType::Orc;
    } else if (typeStr == "Squirrel") {
        type = NpcType::Squirrel;
    } else if (typeStr == "Druid") {
        type = NpcType::Druid;
    } else {
        throw std::invalid_argument("Unknown NPC type: " + typeStr);
    }
    
    return createNPC(type, x, y, name);
}

std::string NPCFactory::serializeNPC(const std::shared_ptr<NPC>& npc) {
    return npc->getTypeName() + " " +
           std::to_string(npc->getX()) + " " +
           std::to_string(npc->getY()) + " " +
           npc->getName();
}