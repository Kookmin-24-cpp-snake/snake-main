/**
 * @file GameProcess.cpp
 * @author hyeoksu
 * @brief 테스트를 위해 임시로 만들었당
 * @date 2024-05-18
 */
#include "GameProcess.h"

GameProcess::GameProcess() : snake(Pos(10, 10), 3, UP), stage(1), direction(UP), currentItem(itemManager.itemMake()){
    map.setDirectory("map/map1.txt");
    map.setMap();
    map.setCoordToValue(currentItem.getCoord().getX(), currentItem.getCoord().getY(), currentItem.getType());
    map.setCoordToValue(snake.getCoord().getX(), snake.getCoord().getY(), 3); // Head
    map.setCoordToValue(snake.getCoord().getX(), snake.getCoord().getY() + 1, 4); // Body
    map.setCoordToValue(snake.getCoord().getX(), snake.getCoord().getY() + 2, 4); // Body
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
                case 5:
                    mvwaddch(stdscr, i, j, 'P' | COLOR_PAIR(2));
                    break;
                case 6:
                    mvwaddch(stdscr, i, j, 'G' | COLOR_PAIR(2));
                    break;
                case 3:
                    mvwaddch(stdscr, i, j, 'H' | COLOR_PAIR(3));
                    break;
                case 4:
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
    // Placeholder logic for updating snake position
    Pos head = snake.getCoord();
    Pos newHead;
    
    switch (direction) {
        case UP:
            newHead = Pos(head.getX(), head.getY() - 1);
            break;
        case DOWN:
            newHead = Pos(head.getX(), head.getY() + 1);
            break;
        case LEFT:
            newHead = Pos(head.getX() - 1, head.getY());
            break;
        case RIGHT:
            newHead = Pos(head.getX() + 1, head.getY());
            break;
    }
    
    // Update map and snake position
    map.setCoordToValue(head.getX(), head.getY(), 4); // Body
    map.setCoordToValue(newHead.getX(), newHead.getY(), 3); // New head
    snake.setCoord(newHead.getX(), newHead.getY());
}

void GameProcess::handleInput() {
    int ch = getch();
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
}

void GameProcess::gameLoop() {
    while (true) {
        handleInput();
        update();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
