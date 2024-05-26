/**
 * @file Pos.h
 * @author hyeoksu
 * @brief Item 및 Snake 구현을 위해 임시로 만들어둔 Pos클래스의 헤더입니다.
 * @date 2024-05-18
 */

#ifndef __POS__
#define __POS__

class Pos{
    int x , y;
public:
    Pos(int x = 0, int y = 0);
    Pos getPos();
    int getX() const;
    int getY() const;
    void setPos(int x , int y);
    bool operator ==(const Pos& coord);
};
#endif