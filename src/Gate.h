#ifndef __GATE__
#define __GATE__
#define GATE 7
#include "Pos.h"
#include <ctime>

class Gate{
    Pos gatePos;
    time_t makedTime;
public:
    Gate(Pos gatePos);
    Gate(int x = 0, int y = 0);
    Pos getCoord() const;
    time_t getTime() const;
    void setGate(Pos coord);
    void setTime(time_t time);
};
#endif