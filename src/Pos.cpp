/**
 * @file Pos.cpp
 * @author hyeoksu
 * @brief 임시 파일 Pos.h를 위한 소스파일입니다.
 * @date 2024-05-18
 */

#include "Pos.h"

Pos::Pos(int x, int y) : x(x), y(y){}

Pos Pos::getPos(){
    return Pos(x,y);
}

int Pos::getX() const{
    return this->x;
}

int Pos::getY() const{
    return this->y;
}

void Pos::setPos(int x, int y){
    this->x = x;
    this->y = y; 
}

bool Pos::operator==(const Pos& coord){
    return ((this->x == coord.x) && (this->y == coord.y));
}