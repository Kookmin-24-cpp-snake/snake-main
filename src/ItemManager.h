/**
 * @file ItemManager.h
 * @author hyeoksu
 * @brief ItemManager를 위한 헤더파일입니다.
 * Map과 Item에 의존합니다.
 * @date 2024-05-18
 */

#ifndef __IMANAGER__
#define __IMANAGER__
#include <cstdlib>
#include <vector>
#include "Map.h"
#include "Item.h"

class ItemManager{
    Map& map;
    int seed;
public:
    ItemManager(Map& map);
    void itemToMap(const Item& item);
    void itemDelete(const Item& item);
    int itemStatus(const Item& item);
    Item itemMake();
    Coord getItemCoord(const Item& item);
};
#endif