#include "UIManager.h"

bool UIManager::getKeyReverse(){
    return this->keyReverse;
}

// 미션 상태 화면에 렌더링
void UIManager::showMissionState(Map& map, StageManager& stageManager) {
    int* missionStatus = stageManager.getMissionStatus();
    bool* missionClear = stageManager.getIsMissionClear();
    const char* missionNames[] = {"LENGTH", "GROWTH", "POISON", "GATE"};

    int xOffset = map.getWidth() + 4;
    int yOffset = 0;
    int boxWidth = 18;
    int boxHeight = 7;
    
    for (int i = 0; i < boxHeight; ++i) {
        for (int j = 0; j < boxWidth; ++j) {
            if (i == 0 || i == boxHeight - 1) {
                mvwaddch(stdscr, yOffset + i, xOffset + j, '-');
            } else if (j == 0 || j == boxWidth - 1) {
                mvwaddch(stdscr, yOffset + i, xOffset + j, '|');
            } else {
                mvwaddch(stdscr, yOffset + i, xOffset + j, ' ');
            }
        }
    }
    mvwaddch(stdscr, yOffset, xOffset, '+');
    mvwaddch(stdscr, yOffset, xOffset + boxWidth - 1, '+');
    mvwaddch(stdscr, yOffset + boxHeight - 1, xOffset, '+');
    mvwaddch(stdscr, yOffset + boxHeight - 1, xOffset + boxWidth - 1, '+');

    mvprintw(yOffset + 1, xOffset + 2, "Mission State:");
    for (int i = 0; i < 4; ++i) {
        mvprintw(yOffset + 2 + i, xOffset + 2, "%s: %d [%c]", missionNames[i], missionStatus[i], missionClear[i] ? 'V' : ' ');
    }
}

// map 화면에 렌더링
void UIManager::render(Map& map) {
    int height = map.getHeight();
    int width = map.getWidth();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int value = map.getMapValue(j, i);
            switch (value) {
                case 0:
                    mvwaddch(stdscr, i, j, ' ' | COLOR_PAIR(1));
                    break;
                case WALL:
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
                case GATE:
                    mvwaddch(stdscr, i, j, '@' | COLOR_PAIR(4));
                    break;
                default:
                    mvwaddch(stdscr, i, j, ' ' | COLOR_PAIR(1));
                    break;
            }
        }
    }
    refresh();
}

// 현재 스테이지 상태 렌더링
void UIManager::showStage(StageManager& sm, Map& map) {
    int xOffset = map.getWidth() + 4;
    int yOffset = 8;
    int boxWidth = 18;
    int boxHeight = 4;
    int stage = sm.getNowStage() + 1;
    int score = sm.getNowScore();

    for (int i = 0; i < boxHeight; ++i) {
        for (int j = 0; j < boxWidth; ++j) {
            if (i == 0 || i == boxHeight - 1) {
                mvwaddch(stdscr, yOffset + i, xOffset + j, '-');
            } else if (j == 0 || j == boxWidth - 1) {
                mvwaddch(stdscr, yOffset + i, xOffset + j, '|');
            } else {
                mvwaddch(stdscr, yOffset + i, xOffset + j, ' ');
            }
        }
    }

    mvwaddch(stdscr, yOffset, xOffset, '+');
    mvwaddch(stdscr, yOffset, xOffset + boxWidth - 1, '+');
    mvwaddch(stdscr, yOffset + boxHeight - 1, xOffset, '+');
    mvwaddch(stdscr, yOffset + boxHeight - 1, xOffset + boxWidth - 1, '+');

    mvprintw(yOffset + 1, xOffset + 2, "Stage: %d", stage);
    mvprintw(yOffset + 2, xOffset + 2, "Score: %d", score);
}


bool UIManager::stopOrPlay(StageManager& stageManager) {
    mvprintw(15, 26, "Clear Stage %d!!", stageManager.getNowStage() + 1);
    mvprintw(16, 26, "Press 'y' to proceed to the next stage.");
    mvprintw(17, 26, "Press 'q' to quit.");


    int ch;
    while (true) {
        ch = getch();
        if (ch != ERR) {
            if (ch == 'y' || ch == 'Y') {
                // 다음 스테이지로 진행
                mvprintw(15, 26, "                                     "); // 메시지 삭제
                mvprintw(16, 26, "                                                                         ");
                mvprintw(17, 26, "                                                                         ");

                return true;  
            } else if(ch == 'q' || ch == 'Q'){
                // 게임 종료
                delwin(stdscr);
                endwin();
                exit(0);
                return false; 
            }
        }
    }
}

// 게임 오버 시 화면에 렌더링
void UIManager::gameOver(GameProcess& game) {
    mvprintw(10, 6, "Game Over~!");
    mvprintw(11, 4,"Press q to quit");
    int ch;
    while (true) {
        ch = getch();
        if (ch != ERR) {
            if (ch == 'q' || ch == 'Q') {
                delwin(stdscr);
                endwin();
                exit(0);
            }
        }
    }
}

// 사용자의 키 값 받기
void UIManager::keyInput(GameProcess& game, Snake& snake) {
    int ch;

    while (true) {
        ch = getch();
        if (ch != ERR) {
            keyPressed = true;
            int direction = game.getDirection();
            switch (ch) {
                case KEY_UP:
                    if (direction != DOWN) game.setDirection(UP);
                    else keyReverse = true;
                    break;
                case KEY_DOWN:
                    if (direction != UP) game.setDirection(DOWN);
                    else keyReverse = true;
                    break;
                case KEY_LEFT:
                    if (direction != RIGHT) game.setDirection(LEFT);
                    else keyReverse = true;
                    break;
                case KEY_RIGHT:
                    if (direction != LEFT) game.setDirection(RIGHT);
                    else keyReverse = true;
                    break;
            }
            snake.insertDirection(game.getDirection());
        } else {
            keyPressed = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

