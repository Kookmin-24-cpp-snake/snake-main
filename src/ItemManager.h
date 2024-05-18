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
#include <ctime>
#include "Map.h"
#include "Item.h"

class ItemManager{
    Map map;
public:
    void itemToMap(const Pos& coord = Pos(0,0), const int& itemType = POISON);
    void itemDelete(const Pos& coord = Pos(0,0));
    int itemStatus(const Item& item);
    Item itemMake();
    Pos getItemCoord(const Item& item);
};
#endif