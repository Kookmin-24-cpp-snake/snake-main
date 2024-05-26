/**
 * @file Item.h
 * @author hyeoksu
 * @brief 아이템 클래스의 헤더 파일
 * @date 2024-05-18
 */

#ifndef __ITEM__
#define __ITEM__
#include <ctime>
#include "Pos.h"

#define POISON 5
#define GROWTH 6

class Item{
    int itemType;
    Pos itemCoord;
    time_t makedTime;
public:
    Item(int type, Pos coord);
    Item(int type = POISON, int x = 0, int y = 0);
    int getType() const;
    Pos getCoord() const;
    time_t getTime() const;
    void setItem(int type, Pos coord);
    void setTime(time_t time);
};
#endif