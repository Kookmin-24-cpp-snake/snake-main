/**
 * @file GameProcess.h
 * @author hyeoksu
 * @brief stage와 main render를 담당하는 클래스
 * Map, Item, Snake
 * @date 2024-05-18
 */

#ifndef __GAMEPROCESS__
#define __GAMEPROCESS__
#include "Map.h"
#include "Item.h"
#include "Snake.h"
#include "ItemManager.h"
#include <ncurses.h>
#include <thread>
#include <chrono>

class GameProcess{
    Map map;
    Snake snake;
    ItemManager itemManager;
    Item currentItem;
    int stage;
    int direction;
public:
    GameProcess();
    void render();
    void update();
    void handleInput();
    void gameLoop();
};
#endif