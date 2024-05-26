#include "Gate.h"

Gate::Gate(Pos coord) : gatePos(coord), makedTime(time(NULL)){}

Gate::Gate(int x, int y) : gatePos(Pos(x,y)), makedTime(time(NULL)){}

Pos Gate::getCoord() const{
    return this->gatePos;
}

void Gate::setGate(Pos coord){
    this->gatePos = coord;
}

void Gate::setTime(time_t time){
    this->makedTime = time;
}

time_t Gate::getTime() const{
    return this->makedTime;
}