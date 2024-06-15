#include "Gate.h"

Gate::Gate(Coord coord) : gatePos(coord), makedTime(time(NULL)){}

Gate::Gate(int x, int y) : gatePos(Coord(x,y)), makedTime(time(NULL)){}

Coord Gate::getCoord() const{
    return this->gatePos;
}

void Gate::setGate(Coord coord){
    this->gatePos = coord;
}

void Gate::setTime(time_t time){
    this->makedTime = time;
}

time_t Gate::getTime() const{
    return this->makedTime;
}