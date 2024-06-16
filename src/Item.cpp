/**
 * @file Item.cpp
 * @author hyeoksu
 * @brief Item.h의 소스파일입니다.
 * @date 2024-05-18
 */

#include "Item.h"

Item::Item(int type, Coord coord) : itemType(type), itemCoord(coord), makedTime(time(NULL)){}

Item::Item(int type, int x, int y) : itemType(type), itemCoord(Coord(x,y)), makedTime(time(NULL)){}

int Item::getType() const{
    return this->itemType;
}

Coord Item::getCoord() const{
    return this->itemCoord;
}

time_t Item::getTime() const{
    return this->makedTime;
}