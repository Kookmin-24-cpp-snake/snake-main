/**
 * @file Item.cpp
 * @author hyeoksu
 * @brief Item.h의 소스파일입니다.
 * @date 2024-05-18
 */

#include "Item.h"

Item::Item(int type, Pos coord) : itemType(type), itemCoord(coord), makedTime(time(NULL)){}

Item::Item(int type, int x, int y) : itemType(type), itemCoord(Pos(x,y)), makedTime(time(NULL)){}

int Item::getType() const{
    return this->itemType;
}

Pos Item::getCoord() const{
    return this->itemCoord;
}

void Item::setItem(int type, Pos coord){
    this->itemType = type;
    this->itemCoord = coord;
}

void Item::setTime(time_t time){
    this->makedTime = time;
}

time_t Item::getTime() const{
    return this->makedTime;
}