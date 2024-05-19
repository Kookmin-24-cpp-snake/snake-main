/**
 * @file ItemManager.cpp
 * @author hyeoksu
 * @brief ItemManager의 소스파일입니다.
 * @date 2024-05-18
 */

#include "ItemManager.h"

ItemManager::ItemManager(Map& map) : map(map){}

void ItemManager::itemToMap(const Item& item){
    map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), item.getType());
}

void ItemManager::itemDelete(const Item& item) {
    map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), 0);
}

int ItemManager::itemStatus(const Item& item) {
    Pos coord = item.getCoord();
    return map.getMapValue(coord.getX(), coord.getY());
}

Item ItemManager::itemMake(int seed) {
    int random, x, y;
    while(true){
        time_t t = time(NULL);
        srand(t + seed);
        random = rand() % 2;
        int h = map.getHeight(); int w = map.getWidth();
        x = rand() % w; y = rand() % h;
        int value = map.getMapValue(x, y);
        if (value == 0) break;
    }
    return Item(POISON+random, x, y);
}

Pos ItemManager::getItemCoord(const Item& item) {
    return item.getCoord();
}