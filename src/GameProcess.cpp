/**
 * @file GameProcess.cpp
 * @author hyeoksu
 * @brief 테스트를 위해 임시로 만들었당
 * @date 2024-05-18
 */
#include "GameProcess.h"

GameProcess::GameProcess(int stageNum) : snake(Pos(10,10) , 3, UP), direction(UP), isGameOver(false), keyPressed(false), stage(stageNum){
    string dir = setStage();
    map.setDirectory(dir);
    map.setMap();
    setSnake();
    item1 = ItemManager(map).itemMake(1);
    item2 = ItemManager(map).itemMake(2);
    item3 = ItemManager(map).itemMake(3);
    setItem();
}

string GameProcess::setStage(){
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

void GameProcess::render() {
    int height = map.getHeight();
    int width = map.getWidth();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int value = map.getMapValue(j, i);
            switch (value) {
                case 0:
                    mvwaddch(stdscr, i, j, ' ' | COLOR_PAIR(1));
                    break;
                case 1:
                    mvwaddch(stdscr, i, j, '-' | COLOR_PAIR(1));
                    break;
                case 2:
                    mvwaddch(stdscr, i, j, '=' | COLOR_PAIR(1));
                    break;
                case POISON:
                    mvwaddch(stdscr, i, j, 'P' | COLOR_PAIR(2));
                    break;
                case GROWTH:
                    mvwaddch(stdscr, i, j, 'G' | COLOR_PAIR(2));
                    break;
                case HEAD:
                    mvwaddch(stdscr, i, j, 'H' | COLOR_PAIR(3));
                    break;
                case TAIL:
                    mvwaddch(stdscr, i, j, 'T' | COLOR_PAIR(3));
                    break;
                default:
                    mvwaddch(stdscr, i, j, ' ' | COLOR_PAIR(1));
                    break;
            }
        }
    }
    refresh();
}

void GameProcess::update() {
    Pos nextHead = snake.nextHead();
    switch(map.getMapValue(nextHead.getX(), nextHead.getY())){
        case POISON:{
        Pos delTail = snake.getTailCoord();
        map.setCoordToValue(delTail.getX(), delTail.getY(), 0);
        snake.getBody().pop_back();
        Item newItem = ItemManager(map).itemMake(3);
        ItemManager(map).itemToMap(item1);
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
        break;
        }

        case 1:{
        gameOver();
        return;
        }
        
        default:
        break;
    }
    Pos tail = snake.getTailCoord();
    map.setCoordToValue(tail.getX(), tail.getY(), 0);
    snake.move();
    setSnake();
}

void GameProcess::keyInput() {
    int ch;
    while (!isGameOver) {
        ch = getch();
        if (ch != ERR) {
            keyPressed = true;
            switch (ch) {
                case KEY_UP:
                    if (direction != DOWN) direction = UP;
                    break;
                case KEY_DOWN:
                    if (direction != UP) direction = DOWN;
                    break;
                case KEY_LEFT:
                    if (direction != RIGHT) direction = LEFT;
                    break;
                case KEY_RIGHT:
                    if (direction != LEFT) direction = RIGHT;
                    break;
            }
            snake.insertDirection(direction);
        } else {
            keyPressed = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void GameProcess::gameLoop() {
    std::thread inputThread(&GameProcess::keyInput, this);

    while (!isGameOver) {
        update();
        render();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    inputThread.join();
}

void GameProcess::gameOver() {
    isGameOver = true;
    mvprintw(10, 6, "Game Over~!");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    endwin();
}