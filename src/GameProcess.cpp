/**
 * @file GameProcess.cpp
 * @author hyeoksu
 * @brief 테스트를 위해 임시로 만들었당
 * @date 2024-05-18
 */
#include "GameProcess.h"

GameProcess::GameProcess(int stageNum) : snake(Pos(10,10) , 3, UP), direction(UP){
    string dir = setStage(1);
    map.setDirectory(dir);
    map.setMap();
    setSnake();
    ItemManager im = ItemManager(map);
    item1 = im.itemMake();
    item2 = im.itemMake();
    item3 = im.itemMake();
    setItem();
}

void GameProcess::initStage(StageManager& stageManager) {
    int stage = stageManager.getNowStage();
    snake = Snake(Pos(10, 10), 3, UP);
    stageManager.initNowStage(snake);
    string dir = setStage(stage+1);
    map.setDirectory(dir);
    map.setMap();
    setSnake();
    ItemManager im = ItemManager(map);
    item1 = im.itemMake();
    item2 = im.itemMake();
    item3 = im.itemMake();
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
    checkItemCycle();
    Pos nextHead = snake.nextHead();
    switch(map.getMapValue(nextHead.getX(), nextHead.getY())){
        case POISON:{
            itemUpdate(stageManager, nextHead, POISON);
            break;
        }

        case GROWTH:{
            itemUpdate(stageManager, nextHead, GROWTH);
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

void GameProcess::checkItemCycle() {
    time_t present = time(nullptr);
    
    // 아이템이 생성된 후의 경과 시간을 계산하여 처리
    checkItemTimeout(item1, present);
    checkItemTimeout(item2, present);
    checkItemTimeout(item3, present);
}

void GameProcess::checkItemTimeout(Item& item, time_t present) {
    int timeDifference = static_cast<int>(present - item.getTime());
    
    if (timeDifference > 10) {
        map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), 0);
        ItemManager im = ItemManager(map);
        item = im.itemMake();
        im.itemToMap(item);
    }
}

void GameProcess::itemUpdate(StageManager& stageManager, Pos nextHead, int type){
    ItemManager im = ItemManager(map);
    switch (type){
        case POISON:{
        Pos delTail = snake.getTailCoord();
        map.setCoordToValue(delTail.getX(), delTail.getY(), 0);
        snake.getBody().pop_back();
        snake.setBody(snake.getBodyLen() - 1);

        if (nextHead.getPos() == item1.getCoord()){
            Item& newItem = item1;
            newItem = im.itemMake();
            im.itemToMap(newItem);
        }
        if (nextHead.getPos() == item2.getCoord()){
            Item& newItem = item2;
            newItem = im.itemMake();
            im.itemToMap(newItem);
        }
        if (nextHead.getPos() == item3.getCoord()){
            Item& newItem = item3;
            newItem = im.itemMake();
            im.itemToMap(newItem);
        }
        
        // StageManager의 미션 상태 및 현재 점수 업데이트
        stageManager.updateMissionStatus(2, 1);
        stageManager.updateNowScore(snake, 2);
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
            snake.setBody(snake.getBodyLen() + 1);

            if (nextHead.getPos() == item1.getCoord()){
                Item& newItem = item1;
                newItem = im.itemMake();
                im.itemToMap(newItem);
            }
            if (nextHead.getPos() == item2.getCoord()){
                Item& newItem = item2;
                newItem = im.itemMake();
                im.itemToMap(newItem);
            }
            if (nextHead.getPos() == item3.getCoord()){
                Item& newItem = item3;
                newItem = ItemManager(map).itemMake();
                im.itemToMap(newItem);
            }
            
            // StageManager의 미션 상태 및 현재 점수 업데이트
            stageManager.updateMissionStatus(1, 1);
            stageManager.updateNowScore(snake, 1);
        }
    }
}

void GameProcess::gameLoop(StageManager& sm, UIManager& um) {
    std::thread inputThread([&](){ um.keyInput(*this, snake); });

    initStage(sm);

    while (true) {
        update(sm, um);
        checkItemCycle();
        um.render(map);
        um.showMissionState(map, sm);
        um.showStage(sm, map);
        this_thread::sleep_for(chrono::milliseconds(500));
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