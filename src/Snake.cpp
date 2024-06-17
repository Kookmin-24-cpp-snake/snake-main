#include "Snake.h"

Snake::Snake(Coord coord, int initBodyLen, int direction) : direction(direction), maxLen(15){
    for (int i = 0; i < initBodyLen; ++i) {
        body.push_back(coord);
        moveCoord(coord, direction);
    }
}

void Snake::moveCoord(Coord& coord, int direction) {
    switch (direction) {
        case UP: coord.setCoord(coord.getX(), coord.getY() + 1); break;
        case DOWN: coord.setCoord(coord.getX(), coord.getY() - 1); break;
        case LEFT: coord.setCoord(coord.getX() + 1, coord.getY()); break;
        case RIGHT: coord.setCoord(coord.getX() - 1, coord.getY()); break;
    }
}

std::deque<Coord>& Snake::getBody() {
    return body;
}

int Snake::getBodyLen() {
    return this->body.size();
}

int Snake::maxBodyLen(){
    return maxLen;
}

int Snake::getDirection() {
    return this->direction;
}

void Snake::setCoord(int x, int y) {
    this->body.front().setCoord(x, y);
}

Coord Snake::getHeadCoord() {
    return this->body.front();
}

Coord Snake::getTailCoord() {
    return this->body.back();
}

void Snake::move() {
    Coord newHead = getHeadCoord();
    switch (direction) {
        case UP:
            newHead.setCoord(newHead.getX(), newHead.getY() - 1);
            break;
        case DOWN:
            newHead.setCoord(newHead.getX(), newHead.getY() + 1);
            break;
        case LEFT:
            newHead.setCoord(newHead.getX() - 1, newHead.getY());
            break;
        case RIGHT:
            newHead.setCoord(newHead.getX() + 1, newHead.getY());
            break;
    }
    body.push_front(newHead);
    body.pop_back();
}

Coord Snake::nextHead(){
    Coord nextHead = getHeadCoord();
    switch (direction) {
        case UP:
            nextHead.setCoord(nextHead.getX(), nextHead.getY() - 1);
            break;
        case DOWN:
            nextHead.setCoord(nextHead.getX(), nextHead.getY() + 1);
            break;
        case LEFT:
            nextHead.setCoord(nextHead.getX() - 1, nextHead.getY());
            break;
        case RIGHT:
            nextHead.setCoord(nextHead.getX() + 1, nextHead.getY());
            break;
    }
    return nextHead;
}

void Snake::insertDirection(int direction) {
    this->direction = direction;
}