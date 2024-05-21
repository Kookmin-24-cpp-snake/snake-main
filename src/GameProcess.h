#ifndef __GAMEPROCESS__
#define __GAMEPROCESS__
#include "Map.h"
#include "Item.h"
#include "Snake.h"
#include "ItemManager.h"
#include <ncurses.h>
#include <thread>
#include <chrono>

class GameProcess {
    Map map;
    Snake snake;
    Item item1, item2, item3;
    int stage;
    int direction;
    bool isGameOver;
    bool keyPressed;

public:
    GameProcess(int stageNum = 1);
    void setSnake();
    string setStage();
    void setItem();
    void render();
    void update();
    void keyInput();
    void gameLoop();
    void gameOver();
};
#endif
