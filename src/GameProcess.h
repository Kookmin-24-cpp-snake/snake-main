#ifndef __GAMEPROCESS__
#define __GAMEPROCESS__
#include "Map.h"
#include "Item.h"
#include "Snake.h"
#include "ItemManager.h"
#include "UIManager.h"
#include "StageManager.h"
#include <ncurses.h>
#include <thread>
#include <chrono>

class UIManager;

class GameProcess {
public:
    Map map;
    Snake snake;
    Item item1, item2, item3;
    int direction;
public:
    GameProcess(int stageNum = 1);
    int getDirection();
    void setDirection(int dir);
    void setSnake();
    void initStage(StageManager& stageManager);
    string setStage(int nowStage);
    void setItem();
    void update(StageManager& sm, UIManager& um);
    void checkItemCycle();
    void checkItemTimeout(Item& item, time_t present);
    void itemUpdate(StageManager& stageManager, Pos nextHead, int type);
    void gameLoop(StageManager& sm, UIManager& um);


    void tmp();
};
#endif