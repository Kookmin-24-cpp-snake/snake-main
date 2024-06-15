/**
 * @file Coord.cpp
 * @author hyeoksu
 * @brief 임시 파일 Coord.h를 위한 소스파일입니다.
 * @date 2024-05-18
 */

#include "Coord.h"

Coord::Coord(int x, int y) : x(x), y(y){}

Coord Coord::getCoord(){
    return Coord(x,y);
}

int Coord::getX() const{
    return this->x;
}

int Coord::getY() const{
    return this->y;
}

void Coord::setCoord(int x, int y){
    this->x = x;
    this->y = y; 
}

bool Coord::operator==(const Coord& coord){
    return ((this->x == coord.x) && (this->y == coord.y));
}