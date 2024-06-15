/**
 * @file ItemManager.cpp
 * @author hyeoksu
 * @brief ItemManager의 소스파일입니다.
 * @date 2024-05-18
 */

#include "ItemManager.h"

ItemManager::ItemManager(Map& map) : map(map){
    srand(static_cast<unsigned int>(time(NULL)));
}

void ItemManager::itemToMap(const Item& item){
    map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), item.getType());
}

void ItemManager::itemDelete(const Item& item) {
    map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), 0);
}

Item ItemManager::itemMake() {
        int random, x, y;
        int h = map.getHeight();
        int w = map.getWidth();
        std::vector<std::pair<int, int>> emptyCoords = map.emptyCoords();

        std::pair<int, int> pos = emptyCoords[rand() % emptyCoords.size()];
        x = pos.first;
        y = pos.second;

        random = rand() % 2;

        return Item(POISON + random, x, y);
}

Coord ItemManager::getItemCoord(const Item& item) {
    return item.getCoord();
}