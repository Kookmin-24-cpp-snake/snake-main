/**
 * @file GameProcess.cpp
 * @author hyeoksu
 * @brief 테스트를 위해 임시로 만들었당
 * @date 2024-05-18
 */
#include "GameProcess.h"

GameProcess::GameProcess(int stageNum) : snake(Pos(10,10) , 3, UP), direction(UP), isGameOver(false){
    string dir = setStage(1);
    map.setDirectory(dir);
    map.setMap();
    setSnake();
    item1 = ItemManager(map).itemMake(1);
    item2 = ItemManager(map).itemMake(2);
    item3 = ItemManager(map).itemMake(3);
    setItem();
}

void GameProcess::initStage(StageManager& stageManager) {
    int stage = stageManager.getNowStage();
    stageManager.initNowStage(snake);
    string dir = setStage(stage+1);
    map.setDirectory(dir);
    map.setMap();
    setSnake();
    item1 = ItemManager(map).itemMake(1);
    item2 = ItemManager(map).itemMake(2);
    item3 = ItemManager(map).itemMake(3);
    setItem();
}

string GameProcess::setStage(int stage){
    switch(stage){
        case 1:
            return "map/map1.txt";
        case 2:
            return "map/map2.txt";
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

void GameProcess::setItem(){
    map.setCoordToValue(item1.getCoord().getX(), item1.getCoord().getY(), item1.getType());
    map.setCoordToValue(item2.getCoord().getX(), item2.getCoord().getY(), item2.getType());
    map.setCoordToValue(item3.getCoord().getX(), item3.getCoord().getY(), item3.getType());
}

void GameProcess::update(StageManager& stageManager, UIManager& um) {
    Pos nextHead = snake.nextHead();
    switch(map.getMapValue(nextHead.getX(), nextHead.getY())){
        case POISON:{
            Pos delTail = snake.getTailCoord();
            map.setCoordToValue(delTail.getX(), delTail.getY(), 0);
            snake.getBody().pop_back();
            Item newItem = ItemManager(map).itemMake(3);
            ItemManager(map).itemToMap(item1);

            // StageManager의 미션 상태 및 현재 점수 업데이트
            stageManager.updateMissionStatus(2, 1);
            stageManager.updateNowScore(snake, 2);
            break;
        }

        case GROWTH:{
            Pos newTail = snake.getTailCoord();
            switch (direction) {
                case UP: newTail.setPos(newTail.getX(), newTail.getY() + 1); break;
                case DOWN: newTail.setPos(newTail.getX(), newTail.getY() - 1); break;
                case LEFT: newTail.setPos(newTail.getX() + 1, newTail.getY()); break;
                case RIGHT: newTail.setPos(newTail.getX() - 1, newTail.getY()); break;
            }
            snake.getBody().push_back(newTail);
            Item newItem = ItemManager(map).itemMake(1);
            ItemManager(map).itemToMap(item1);
            
            // StageManager의 미션 상태 및 현재 점수 업데이트
            stageManager.updateMissionStatus(1, 1);
            stageManager.updateNowScore(snake, 1);
            break;
        }

        case 1:{
            um.gameOver(*this);
            return;
        }

        default:
            break;
    }
    Pos tail = snake.getTailCoord();
    map.setCoordToValue(tail.getX(), tail.getY(), 0);
    snake.move();
    setSnake();

    // 미션 완료 시, 다음 스테이지
    if (stageManager.checkMissionClear()) {
        bool isPlay = um.stopOrPlay(stageManager);
        if (isPlay) {
            stageManager.setNowStage();
            initStage(stageManager);
        }
    }
}

void GameProcess::gameLoop(StageManager& sm, UIManager& um) {
    std::thread inputThread([&](){ um.keyInput(*this, snake); });

    initStage(sm);

    while (!isGameOver) {
        update(sm, um);
        um.render(map);
        um.showMissionState(map, sm);
        um.showStage(sm, map);
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    inputThread.join();
}

// 접근자 설정자
bool GameProcess::getIsGameOver() {
    return isGameOver;
}

void GameProcess::setIsGameOver(bool tf) {
    isGameOver = tf;
}

int GameProcess::getDirection() {
    return direction;
}

void GameProcess::setDirection(int dir) {
    direction = dir;
}