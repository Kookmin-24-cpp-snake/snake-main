#ifndef __SNAKE__
#define __SNAKE__
#include "Pos.h"
#include <deque>

#define HEAD 3
#define TAIL 4
#define UP 11
#define DOWN 12
#define LEFT 13
#define RIGHT 14

class Snake {
    std::deque<Pos> body;
    int direction;
    int bodyLen;
    int maxLen;

public:
    Snake(Pos coord = Pos(0, 0), int bodyLen = 3, int direction = LEFT, int maxLen = 15);
    void setBody(int len);
    int getBodyLen();
    int maxBodyLen();
    int getDirection();
    std::deque<Pos> getBody();
    void setCoord(int x = 0, int y = 0);
    Pos getHeadCoord();
    Pos getTailCoord();
    void move();
    Pos nextHead();
    void insertDirection(int direction);
};
#endif