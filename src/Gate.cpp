#include "Gate.h"

Gate::Gate(Coord coord) : gatePos(coord), makedTime(time(NULL)){}

Gate::Gate(int x, int y) : gatePos(Coord(x,y)), makedTime(time(NULL)){}

Coord Gate::getCoord() const{
    return this->gatePos;
}

time_t Gate::getTime() const{
    return this->makedTime;
}