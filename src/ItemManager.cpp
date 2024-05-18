/**
 * @file ItemManager.cpp
 * @author hyeoksu
 * @brief ItemManager의 소스파일입니다.
 * @date 2024-05-18
 */

#include "ItemManager.h"

void ItemManager::itemToMap(const Pos& coord, const int& itemType){
    map.setCoordToValue(coord.getX(), coord.getY(), itemType);
}

void ItemManager::itemDelete(const Pos& coord) {
    map.setCoordToValue(coord.getX(), coord.getY(), 0);
}

int ItemManager::itemStatus(const Item& item) {
    Pos coord = item.getCoord();
    return map.getMapValue(coord.getX(), coord.getY());
}

int ItemManager::itemMake() {
    time_t t = time(NULL);
    srand(t);
    int random = rand() % 2;
    int h = map.getHeight(); int w = map.getWidth();
    int x = rand() % w; int y = rand() % h;
    map.setCoordToValue(x, y, POISON + random);
}

Pos ItemManager::getItemCoord(const Item& item) {
    return item.getCoord();
}