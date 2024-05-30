/**
 * @file GameProcess.cpp
 * @brief 게임 프로세스 구현 파일
 */

#include "GameProcess.h"

GameProcess::GameProcess(int stageNum)
    : snake(Pos(4, 1), 3, RIGHT), direction(RIGHT), im(map), gm(map), gateUsing(false), gateSup(-1){
    initializeStage(stageNum);
}

void GameProcess::initializeStage(int stageNum) {
    std::string dir = getStageDirectory(stageNum);
    map.setDirectory(dir);
    map.setMap();
    setSnake();
    item1 = im.itemMake();
    item2 = im.itemMake();
    item3 = im.itemMake();
    gate1 = gm.GateMake();
    gate2 = gm.GateMake();
    setItemsOnMap();
}

void GameProcess::initStage(StageManager& stageManager) {
    int stage = stageManager.getNowStage();
    snake = Snake(Pos(4, 1), 3, RIGHT);
    direction = RIGHT;
    stageManager.initNowStage(snake);
    initializeStage(stage + 1);
}

std::string GameProcess::getStageDirectory(int stage) {
    switch (stage) {
        case 1:
            return "map/map1.txt";
        case 2:
            return "map/map2.txt";
        case 3:
            return "map/map3.txt";
        case 4:
            return "map/map4.txt";
        default:
            return "map/map1.txt";
    }
}

void GameProcess::setSnake() {
    for (const Pos &part : snake.getBody()) {
        map.setCoordToValue(part.getX(), part.getY(), TAIL);
    }
    map.setCoordToValue(snake.getHeadCoord().getX(), snake.getHeadCoord().getY(), HEAD);
}

void GameProcess::setItemsOnMap() {
    setItemOnMap(item1);
    setItemOnMap(item2);
    setItemOnMap(item3);
}

void GameProcess::setItemOnMap(const Item& item) {
    map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), item.getType());
}

void GameProcess::setGatesOnMap() {
    setGateOnMap(gate1);
    setGateOnMap(gate2);
}

void GameProcess::setGateOnMap(const Gate& gate) {
    map.setCoordToValue(gate.getCoord().getX(), gate.getCoord().getY(), GATE);
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

    Pos nextHead = snake.nextHead();
    int mapValue = map.getMapValue(nextHead.getX(), nextHead.getY());

    if (um.getKeyReverse()) um.gameOver(*this);
    if (mapValue == POISON) {
        itemUpdate(stageManager, nextHead, POISON);
        moveSnake();
        setSnake();
    } else if (mapValue == GROWTH) {
        itemUpdate(stageManager, nextHead, GROWTH);
        moveSnake();
        Pos newTail = snake.getTailCoord();
        snake.getBody().push_back(newTail);
        setSnake();
    } else if (mapValue == WALL) {
        um.gameOver(*this);
        return;
    } else if (mapValue == TAIL){
        um.gameOver(*this);
    }
    else if (mapValue == GATE){
        gateSup = snake.getBodyLen();
        gateUpdate(stageManager, nextHead);
        setSnake();

    }
    else{
        moveSnake();
        setSnake();
    }

    if (--gateSup == 0) gateUsing = false;


}

void GameProcess::moveSnake() {
    Pos tail = snake.getTailCoord();
    map.setCoordToValue(tail.getX(), tail.getY(), 0);
    snake.move();
}

void GameProcess::checkItemCycle() {
    time_t present = time(nullptr);
    checkItemTimeout(item1, present);
    checkItemTimeout(item2, present);
    checkItemTimeout(item3, present);
}

void GameProcess::checkItemTimeout(Item& item, time_t present) {
    int timeDifference = static_cast<int>(present - item.getTime());
    if (timeDifference > 10) {
        map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), 0);
        item = im.itemMake();
        im.itemToMap(item);
    }
}

void GameProcess::checkGateCycle() {
    time_t present = time(nullptr);
    checkGateTimeout(gate1, present);
    checkGateTimeout(gate2, present);
}

void GameProcess::checkGateTimeout(Gate& gate, time_t present) {
    int timeDifference = static_cast<int>(present - gate.getTime());
    if (timeDifference > 10 && !(gateUsing)) {
        map.setCoordToValue(gate.getCoord().getX(), gate.getCoord().getY(), WALL);
        gate = gm.GateMake();
        gm.GateToMap(gate);
    }
}

void GameProcess::replaceItemIfMatch(Item& item, Pos& nextHead) {
    if (nextHead.getPos() == item.getCoord()) {
        item = im.itemMake();
        im.itemToMap(item);
    }
}

void GameProcess::itemUpdate(StageManager& stageManager, Pos nextHead, int type) {
    switch (type) {
        case POISON:
            processPoisonItem(stageManager, nextHead);
            break;
        case GROWTH:
            processGrowthItem(stageManager, nextHead);
            break;
    }
}

void GameProcess::gateUpdate(StageManager& stageManager, Pos nextHead) {
    gateUsing =true;
    map.setCoordToValue(snake.getBody().back().getX(), snake.getBody().back().getY(), 0);
    snake.getBody().pop_back();
    if (nextHead == gate1.getCoord()){
        Pos newHead = validDirection(gate2.getCoord());
        snake.getBody().push_front(newHead);
    }
    if (nextHead == gate2.getCoord()){
        Pos newHead = validDirection(gate1.getCoord());
        snake.getBody().push_front(newHead);
    }
    stageManager.updateMissionStatus(3, 1);
    stageManager.updateNowScore(snake, 3);
}

Pos GameProcess::validDirection(Pos gateCoord){
    int x = gateCoord.getX(); int y = gateCoord.getY();
    int h = map.getHeight(); int w = map.getWidth();
    if (x == w - 1) {
        setDirection(LEFT);
        snake.insertDirection(LEFT);
        return Pos(x - 1, y);
    }
    else if (x == 0){
        setDirection(RIGHT);
        snake.insertDirection(RIGHT);
        return Pos(x + 1, y);
    }
    else if (y == h - 1){
        setDirection(UP);
        snake.insertDirection(UP);
        return Pos(x, y - 1);
    }
    else if (y == 0){
        setDirection(DOWN);
        snake.insertDirection(DOWN);
        return Pos(x, y + 1);
    }
    else{
        if (direction == UP){
            if (map.getMapValue(x, y - 1) != WALL
            && map.getMapValue(x, y - 1) != IMMUNE) return Pos(x, y - 1);
            else if (map.getMapValue(x + 1, y) != WALL
            && map.getMapValue(x + 1, y) != IMMUNE){
                setDirection(RIGHT);
                snake.insertDirection(RIGHT);
                return Pos(x + 1, y);
            }
            else if (map.getMapValue(x - 1, y) != WALL
            && map.getMapValue(x - 1, y) != IMMUNE) {
                setDirection(LEFT);
                snake.insertDirection(LEFT);
                return Pos(x - 1, y);
            }
            else if (map.getMapValue(x, y + 1) != WALL
            && map.getMapValue(x, y + 1) != IMMUNE){
                setDirection(DOWN);
                snake.insertDirection(DOWN);
                return Pos(x, y + 1);
            }
            else return Pos();
        }

        else if (direction == DOWN){
            if (map.getMapValue(x, y + 1) != WALL
            && map.getMapValue(x, y + 1) != IMMUNE) return Pos(x, y + 1);
            else if (map.getMapValue(x - 1, y) != WALL\
            && map.getMapValue(x - 1, y) != IMMUNE){
                setDirection(LEFT);
                snake.insertDirection(LEFT);
                return Pos(x - 1, y);
            }
            else if (map.getMapValue(x + 1, y) != WALL
            && map.getMapValue(x + 1, y) != IMMUNE) {
                setDirection(RIGHT);
                snake.insertDirection(RIGHT);
                return Pos(x + 1, y);
            }
            else if (map.getMapValue(x, y - 1) != WALL
            && map.getMapValue(x, y - 1) != IMMUNE){
                setDirection(UP);
                snake.insertDirection(UP);
                return Pos(x, y - 1);
            }
            else return Pos();
        }

        else if (direction == LEFT){
            if (map.getMapValue(x - 1, y) != WALL
            && map.getMapValue(x - 1, y) != IMMUNE) return Pos(x - 1, y);
            else if (map.getMapValue(x, y - 1) != WALL
            && map.getMapValue(x, y - 1) != IMMUNE){
                setDirection(UP);
                snake.insertDirection(UP);
                return Pos(x, y - 1);
            }
            else if (map.getMapValue(x, y + 1) != WALL
            && map.getMapValue(x, y + 1) != IMMUNE) {
                setDirection(DOWN);
                snake.insertDirection(DOWN);
                return Pos(x, y + 1);
            }
            else if (map.getMapValue(x + 1, y) != WALL
            && map.getMapValue(x + 1, y) != IMMUNE) {
                setDirection(RIGHT);
                snake.insertDirection(RIGHT);
                return Pos(x + 1, y);
            }
            else return Pos();
        }

        else{
            if (map.getMapValue(x + 1, y) != WALL
            && map.getMapValue(x + 1, y) != IMMUNE) return Pos(x + 1, y);
            else if (map.getMapValue(x, y + 1) != WALL
            && map.getMapValue(x, y + 1) != IMMUNE) {
                setDirection(DOWN);
                snake.insertDirection(DOWN);
                return Pos(x, y + 1);
            }
            else if (map.getMapValue(x, y - 1) != WALL
            && map.getMapValue(x, y - 1) != IMMUNE){
                setDirection(UP);
                snake.insertDirection(UP);
                return Pos(x, y - 1);
            }
            else if (map.getMapValue(x - 1, y) != WALL
            && map.getMapValue(x - 1, y) != IMMUNE) {
                setDirection(LEFT);
                snake.insertDirection(LEFT);
                return Pos(x - 1, y);
            }
            else return Pos();
        }
    }
}

void GameProcess::processPoisonItem(StageManager& stageManager, Pos nextHead) {
    Pos delTail = snake.getTailCoord();
    map.setCoordToValue(delTail.getX(), delTail.getY(), 0);
    snake.getBody().pop_back();

    replaceItemIfMatch(item1, nextHead);
    replaceItemIfMatch(item2, nextHead);
    replaceItemIfMatch(item3, nextHead);

    stageManager.updateMissionStatus(2, 1);
    stageManager.updateNowScore(snake, 2);
}

void GameProcess::processGrowthItem(StageManager& stageManager, Pos nextHead) {
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
        checkItemCycle();
        checkGateCycle();
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
    direction = dir;
}