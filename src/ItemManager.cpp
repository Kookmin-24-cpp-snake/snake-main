/**
 * @file ItemManager.cpp
 * @author hyeoksu
 * @brief ItemManager의 소스파일입니다.
 * @date 2024-05-18
 */

#include "ItemManager.h"

ItemManager::ItemManager(Map& map) : map(map), seed(0){
    srand(static_cast<unsigned int>(time(NULL)));
}

void ItemManager::itemToMap(const Item& item){
    map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), item.getType());
}

void ItemManager::itemDelete(const Item& item) {
    map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), 0);
}

int ItemManager::itemStatus(const Item& item) {
    Coord coord = item.getCoord();
    return map.getMapValue(coord.getX(), coord.getY());
}

Item ItemManager::itemMake() {
        int random, x, y;
        int h = map.getHeight();
        int w = map.getWidth();
        std::vector<std::pair<int, int>> emptyPositions;

        // 모든 빈 위치 수집
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (map.getMapValue(i, j) == 0) {
                    emptyPositions.push_back(std::make_pair(i, j));
                }
            }
        }

        // 무작위로 빈 위치 선택
        std::pair<int, int> pos = emptyPositions[rand() % emptyPositions.size()];
        x = pos.first;
        y = pos.second;

        random = rand() % 2;
        seed += 1; // 시드 증가 (다른 곳에서 필요할 경우를 대비)

        return Item(POISON + random, x, y);
}

Coord ItemManager::getItemCoord(const Item& item) {
    return item.getCoord();
}