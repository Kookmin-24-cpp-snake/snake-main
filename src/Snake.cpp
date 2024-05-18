/**
 * @file Snake.cpp
 * @author hyeoksu
 * @brief Snake.h의 소스파일입니다.
 * @date 2024-05-18
 */

#include "Snake.h"

Snake::Snake(Pos coord, int body, int direction) : sCoord(coord), body(body), direction(direction){}
Snake::Snake(int x, int y, int body, int direction) : sCoord(Pos(x,y)), body(body), direction(direction){}
int Snake::getBody(){
    return this->body;
}

int Snake::getDirection(){
    return this->direction;
}

void Snake::setCoord(int x, int y){
    this->sCoord.setPos(x, y);
}

Pos Snake::getCoord(){
    return this->sCoord;
}

void Snake::insertDirection(int direction){
    this->direction = direction;
}
void Snake::eatItem(int itemType){
    if (itemType == 5) this->body--;
    else this->body++;
}