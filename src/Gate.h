#ifndef __GATE__
#define __GATE__
#define GATE 7
#include "Coord.h"
#include <ctime>

class Gate{
    Coord gatePos;
    time_t makedTime;
public:
    Gate(Coord gatePos);
    Gate(int x = 0, int y = 0);
    Coord getCoord() const;
    time_t getTime() const;
};
#endif