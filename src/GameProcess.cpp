/**
 * @file GameProcess.cpp
 * @brief 게임 프로세스 구현 파일
 */
#include "GameProcess.h"

GameProcess::GameProcess(int stageNum)
    : snake(Coord(4, 1), 3, RIGHT), direction(RIGHT), im(map), gm(map), gateUsing(false), gateSup(-1){
    initializeStage(stageNum);
}

void GameProcess::initializeStage(int stageNum) {
    std::string dir = map.getStageDirectory(stageNum);
    map.setDirectory(dir);
    map.setMap();
    setSnake();
    item1 = im.itemMake(); item2 = im.itemMake(); item3 = im.itemMake();
    gate1 = Gate(); gate2 = Gate();
    im.setItemsOnMap(item1, item2, item3);
}

void GameProcess::initStage(StageManager& stageManager) {
    int stage = stageManager.getNowStage();
    snake = Snake(Coord(4, 1), 3, RIGHT);
    direction = RIGHT;
    stageManager.initNowStage(snake);
    initializeStage(stage + 1);
}

void GameProcess::setSnake() {
    for (const Coord &part : snake.getBody()) map.setCoordToValue(part.getX(), part.getY(), TAIL);
    map.setCoordToValue(snake.getHeadCoord().getX(), snake.getHeadCoord().getY(), HEAD);
}

void GameProcess::update(StageManager& stageManager, UIManager& um) {
    if (stageManager.checkMissionClear()) {
        if (stageManager.getNowStage() == 3) {
            bool isReplay = um.showGameClearPrompt();
            if (isReplay) {
                stageManager.setNowStage(0);
                initStage(stageManager);
            }
            
        }
        else if (um.stopOrPlay(stageManager)) {
            stageManager.setNowStage();
            initStage(stageManager);
        }

    }
    if (snake.getBodyLen() < 3) {
        um.gameOver(*this);
        return;
    }

    Coord nextHead = snake.nextHead();
    int mapValue = map.getMapValue(nextHead.getX(), nextHead.getY());
    if (um.getKeyReverse() || mapValue == WALL || mapValue == TAIL) {
        um.gameOver(*this);
        return;
    }
    if (mapValue == POISON) {
        itemUpdate(stageManager, nextHead, POISON);
        moveSnake();
        setSnake();
    } else if (mapValue == GROWTH) {
        itemUpdate(stageManager, nextHead, GROWTH);
        moveSnake();
        Coord newTail = snake.getTailCoord();
        snake.getBody().push_back(newTail);
        setSnake();
    } else if (mapValue == GATE){
        gateSup = snake.getBodyLen();
        gateUpdate(stageManager, nextHead);
        setSnake();
    } else{
        moveSnake();
        setSnake();
    }
    if (--gateSup == 0) gateUsing = false;
}

void GameProcess::moveSnake() {
    Coord tail = snake.getTailCoord();
    map.setCoordToValue(tail.getX(), tail.getY(), 0);
    snake.move();
}

void GameProcess::replaceItemIfMatch(Item& item, Coord& nextHead) {
    if (nextHead.getCoord() == item.getCoord()) {
        item = im.itemMake();
        im.itemToMap(item);
    }
}

void GameProcess::itemUpdate(StageManager& stageManager, Coord nextHead, int type) {
    switch (type) {
        case POISON:
            processPoisonItem(stageManager, nextHead);
            break;
        case GROWTH:
            processGrowthItem(stageManager, nextHead);
            break;
    }
}

void GameProcess::gateUpdate(StageManager& stageManager, Coord nextHead) {
    gateUsing =true;
    map.setCoordToValue(snake.getBody().back().getX(), snake.getBody().back().getY(), 0);
    snake.getBody().pop_back();
    if (nextHead == gate1.getCoord()){
        Coord newHead = validDirection(gate2.getCoord());
        snake.getBody().push_front(newHead);
    }
    if (nextHead == gate2.getCoord()){
        Coord newHead = validDirection(gate1.getCoord());
        snake.getBody().push_front(newHead);
    }
    stageManager.updateMissionStatus(3, 1);
    stageManager.updateNowScore(snake, 3);
}

Coord GameProcess::validDirection(Coord gateCoord) {
    int x = gateCoord.getX();
    int y = gateCoord.getY();
    int h = map.getHeight();
    int w = map.getWidth();

    const int dx[] = {0, 1, 0, -1}; // UP, RIGHT, DOWN, LEFT
    const int dy[] = {-1, 0, 1, 0}; // UP, RIGHT, DOWN, LEFT
    const int directions[] = {UP, RIGHT, DOWN, LEFT};

    if (x == w - 1) {
        setDirection(LEFT);
        return Coord(x - 1, y);
    } else if (x == 0) {
        setDirection(RIGHT);
        return Coord(x + 1, y);
    } else if (y == h - 1) {
        setDirection(UP);
        return Coord(x, y - 1);
    } else if (y == 0) {
        setDirection(DOWN);
        return Coord(x, y + 1);
    }

    int startIdx;
    switch (direction) {
        case UP: startIdx = 0; break;
        case RIGHT: startIdx = 1; break;
        case DOWN: startIdx = 2; break;
        case LEFT: startIdx = 3; break;
    }

    int newX = x + dx[startIdx];
    int newY = y + dy[startIdx];
    if (map.getMapValue(newX, newY) != WALL && map.getMapValue(newX, newY) != IMMUNE) {
        return Coord(newX, newY);
    }

    newX = x + dx[(startIdx + 1) % 4];
    newY = y + dy[(startIdx + 1) % 4];
    if (map.getMapValue(newX, newY) != WALL && map.getMapValue(newX, newY) != IMMUNE) {
        setDirection(directions[(startIdx + 1) % 4]);
        return Coord(newX, newY);
    }

    newX = x + dx[(startIdx + 3) % 4];
    newY = y + dy[(startIdx + 3) % 4];
    if (map.getMapValue(newX, newY) != WALL && map.getMapValue(newX, newY) != IMMUNE) {
        setDirection(directions[(startIdx + 3) % 4]);
        return Coord(newX, newY);
    }

    newX = x + dx[(startIdx + 2) % 4];
    newY = y + dy[(startIdx + 2) % 4];
    if (map.getMapValue(newX, newY) != WALL && map.getMapValue(newX, newY) != IMMUNE) {
        setDirection(directions[(startIdx + 2) % 4]);
        return Coord(newX, newY);
    }

    return Coord();
}

void GameProcess::processPoisonItem(StageManager& stageManager, Coord nextHead) {
    Coord delTail = snake.getTailCoord();
    map.setCoordToValue(delTail.getX(), delTail.getY(), 0);
    snake.getBody().pop_back();

    replaceItemIfMatch(item1, nextHead);
    replaceItemIfMatch(item2, nextHead);
    replaceItemIfMatch(item3, nextHead);

    stageManager.updateMissionStatus(2, 1);
    stageManager.updateNowScore(snake, 2);
}

void GameProcess::processGrowthItem(StageManager& stageManager, Coord nextHead) {
    replaceItemIfMatch(item1, nextHead);
    replaceItemIfMatch(item2, nextHead);
    replaceItemIfMatch(item3, nextHead);

    stageManager.updateMissionStatus(1, 1);
    stageManager.updateNowScore(snake, 1);
}

void GameProcess::gameLoop(StageManager& sm, UIManager& um) {
    std::thread inputThread([&](){ um.keyInput(*this, snake); });

    initStage(sm);

    while (true) {
        update(sm, um);
        im.checkItemCycle(item1, item2, item3);
        if(!(gateUsing)) gm.checkGateCycle(gate1, gate2);
        um.render(map);
        um.showMissionState(map, sm);
        um.showStage(sm, map);
        std::this_thread::sleep_for(std::chrono::milliseconds(350));
    }
    inputThread.join();
}

// 접근자 설정자
int GameProcess::getDirection() {
    return direction;
}
void GameProcess::setDirection(int dir) {
    snake.insertDirection(dir);
    direction = dir;
}