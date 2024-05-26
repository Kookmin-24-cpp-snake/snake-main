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
#include "Map.h"
#include "Item.h"

#ifndef __SEED__
#define __SEED__
extern int seed; // seed값으로 사용할 int type 전역 변수
#endif

class ItemManager{
    Map& map;
public:
    ItemManager(Map& map);
    void itemToMap(const Item& item);
    void itemDelete(const Item& item);
    int itemStatus(const Item& item);
    Item itemMake();
    Pos getItemCoord(const Item& item);
};
#endif