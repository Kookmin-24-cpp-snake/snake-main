/**
 * @file Item.h
 * @author hyeoksu
 * @brief 아이템 클래스의 헤더 파일
 * @date 2024-05-18
 */

#ifndef __ITEM__
#define __ITEM__
#include "Pos.h"

#define POISON 5
#define GROWTH 6

class Item{
    int itemType;
    Pos itemCoord;
public:
    Item(int type, Pos coord);
    Item(int type = POISON, int x = 0, int y = 0);
    int getType() const;
    Pos getCoord() const;
    void setItem(int type, Pos coord);
};
#endif