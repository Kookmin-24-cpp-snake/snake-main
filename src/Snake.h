#ifndef __SNAKE__
#define __SNAKE__
#include "Coord.h"
#include <deque>

#define HEAD 3
#define TAIL 4
#define UP 11
#define DOWN 12
#define LEFT 13
#define RIGHT 14

class Snake {
    std::deque<Coord> body;
    int direction;
    int initBodyLen;
    int maxLen;

public:
    Snake(Coord coord = Coord(0, 0), int initBodyLen = 3, int direction = LEFT);
    void moveCoord(Coord& coord, int direction);
    int getBodyLen();
    int maxBodyLen();
    int getDirection();
    std::deque<Coord>& getBody();
    void setCoord(int x = 0, int y = 0);
    Coord getHeadCoord();
    Coord getTailCoord();
    void move();
    Coord nextHead();
    void insertDirection(int direction);
};
#endif