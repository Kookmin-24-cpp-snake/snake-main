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

void ItemManager::setItemsOnMap(Item& item1, Item& item2, Item& item3) {
    itemToMap(item1);
    itemToMap(item2);
    itemToMap(item3);
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

    random = rand() % 100;
    if (random < 10) { 
        return Item(RANDOM, x, y);
    } else if (random < 55) { 
        return Item(GROWTH, x, y);
    } else {
        return Item(POISON, x, y);
    }
}

Coord ItemManager::getItemCoord(const Item& item) {
    return item.getCoord();
}

void ItemManager::checkItemCycle(Item& item1, Item& item2, Item& item3) {
    time_t present = time(nullptr);
    checkItemTimeout(item1, present);
    checkItemTimeout(item2, present);
    checkItemTimeout(item3, present);
}

void ItemManager::checkItemTimeout(Item& item, time_t present) {
    int timeDifference = static_cast<int>(present - item.getTime());
    if (timeDifference > 10) {
        itemDelete(item);
        item = itemMake();
        itemToMap(item);
    }
}