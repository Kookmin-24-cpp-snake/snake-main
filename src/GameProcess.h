#ifndef __GAMEPROCESS__
#define __GAMEPROCESS__
#include "Map.h"
#include "Item.h"
#include "Snake.h"
#include "ItemManager.h"
#include "UIManager.h"
#include "StageManager.h"
#include "GateManager.h"
#include <ncurses.h>
#include <thread>
#include <chrono>

#define WALL 1
#define IMMUNE 2

class UIManager;

class GameProcess {
public:
    Map map;
    Snake snake;
    Gate gate1, gate2;
    Item item1, item2, item3;
    ItemManager im;
    GateManager gm;
    int direction;
    int gateSup;
    bool gateUsing;
public:
    GameProcess(int stageNum = 1);
    void initializeStage(int stageNum);
    std::string getStageDirectory(int stageNum);
    void setItemOnMap(const Item& item);
    void setGateOnMap(const Gate& gate);
    void setGatesOnMap();
    int getDirection();
    void setDirection(int dir);
    void setSnake();
    void initStage(StageManager& stageManager);
    void setItemsOnMap();
    void moveSnake();
    void update(StageManager& sm, UIManager& um);
    void checkItemCycle();
    void checkItemTimeout(Item& item, time_t present);
    void checkGateCycle();
    void checkGateTimeout(Gate& gate, time_t present);
    void itemUpdate(StageManager& stageManager, Coord nextHead, int type);
    void gateUpdate(StageManager& stageManager, Coord nextHead);
    Coord validDirection(Coord gate);
    void gameLoop(StageManager& sm, UIManager& um);
    void replaceItemIfMatch(Item& item, Coord& nextHead);
    void processPoisonItem(StageManager& stageManager, Coord nextHead);
    void processGrowthItem(StageManager& stageManager, Coord nextHead);
};
#endif