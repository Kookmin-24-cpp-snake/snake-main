/**
 * @file MainTest.cpp
 * @brief GameProcess를 테스트하는 메인 파일입니다.
 * @date 2024-05-18
 */

#include "GameProcess.h"
#include "UIManager.h"
#include "StageManager.h"

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    nodelay(stdscr, true);

    GameProcess game;
    UIManager um;
    StageManager sm;
    game.gameLoop(sm, um);
    return 0;
}