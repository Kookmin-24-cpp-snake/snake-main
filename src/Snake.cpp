#include "Snake.h"

Snake::Snake(Pos coord, int bodyLen, int direction) : direction(direction) {
    for (int i = 0; i < bodyLen; ++i){
        body.push_back(coord);
        switch (direction) {
            case UP: coord.setPos(coord.getX(), coord.getY() + 1); break;
            case DOWN: coord.setPos(coord.getX(), coord.getY() - 1); break;
            case LEFT: coord.setPos(coord.getX() + 1, coord.getY()); break;
            case RIGHT: coord.setPos(coord.getX() - 1, coord.getY()); break;
        }
    }
}

int Snake::getBodyLen() {
    return this->body.size();
}

int Snake::getDirection() {
    return this->direction;
}

std::deque<Pos> Snake::getBody() {
    return body;
}

void Snake::setCoord(int x, int y) {
    this->body.front().setPos(x, y);
}

Pos Snake::getHeadCoord() {
    return this->body.front();
}

Pos Snake::getTailCoord() {
    return this->body.back();
}

void Snake::move() {
    Pos newHead = getHeadCoord();
    switch (direction) {
        case UP:
            newHead.setPos(newHead.getX(), newHead.getY() - 1);
            break;
        case DOWN:
            newHead.setPos(newHead.getX(), newHead.getY() + 1);
            break;
        case LEFT:
            newHead.setPos(newHead.getX() - 1, newHead.getY());
            break;
        case RIGHT:
            newHead.setPos(newHead.getX() + 1, newHead.getY());
            break;
    }
    body.push_front(newHead);
    body.pop_back();
}

Pos Snake::nextHead(){
    Pos nextHead = getHeadCoord();
    switch (direction) {
        case UP:
            nextHead.setPos(nextHead.getX(), nextHead.getY() - 1);
            break;
        case DOWN:
            nextHead.setPos(nextHead.getX(), nextHead.getY() + 1);
            break;
        case LEFT:
            nextHead.setPos(nextHead.getX() - 1, nextHead.getY());
            break;
        case RIGHT:
            nextHead.setPos(nextHead.getX() + 1, nextHead.getY());
            break;
    }
    return nextHead;
}

void Snake::insertDirection(int direction) {
    this->direction = direction;
}