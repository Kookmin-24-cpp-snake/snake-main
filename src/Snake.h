/**
 * @file Snake.h
 * @author hyeoksu
 * @brief Snake class의 헤더파일입니다.
 * Pos에 의존합니다.
 * @date 2024-05-18
 */

#ifndef __SNAKE__
#define __SNAKE__
#include "Pos.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class Snake{
    Pos sCoord;
    int body;
    int direction;
public:
    Snake(Pos coord = Pos(0,0), int body = 3, int direction = LEFT);
    Snake(int x = 0, int y = 0, int body = 3, int direction = LEFT);
    int getBody();
    int getDirection();
    Pos getCoord();
    void insertDirection(int direction);
    void eatItem(int itemType);
};
#endif