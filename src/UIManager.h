#ifndef __UI_MANAGER__
#define __UI_MANAGER__

#include "Map.h"
#include "ItemManager.h"
#include "Snake.h"
#include "GameProcess.h"
#include "StageManager.h"
#include "GateManager.h"

#include <ncurses.h>

class GameProcess;

class UIManager {
    bool keyPressed;
public:
    void render(Map& map);
    void gameOver(GameProcess& game);
    void keyInput(GameProcess& game, Snake& snake);
    void showMissionState(Map& map, StageManager& stageManager);
    void showStage(StageManager& stageManager, Map& map);
    bool stopOrPlay(StageManager& StageManager);
};

#endif
