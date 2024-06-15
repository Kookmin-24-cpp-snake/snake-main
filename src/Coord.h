/**
 * @file Coord.h
 * @author hyeoksu
 * @brief Item 및 Snake 구현을 위해 임시로 만들어둔 Pos클래스의 헤더입니다.
 * @date 2024-05-18
 */

#ifndef __POS__
#define __POS__

class Coord{
    int x , y;
public:
    Coord(int x = 0, int y = 0);
    Coord getCoord();
    int getX() const;
    int getY() const;
    void setCoord(int x , int y);
    bool operator ==(const Coord& coord);
};
#endif