/**
 * @file MapTest.cpp
 * @author hyeoksu
 * @brief Map 클래스가 정상 작동하는지 확인하는 코드입니다.
 * make MapTest로 실행 가능합니다.
 * @date 2024-05-18
 */
#include <ncurses.h>
#include "Map.h"

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    Map map;
    map.setDirectory("map/map2.txt");
    map.setMap();
    int height = map.getHeight();
    int width = map.getWidth();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            switch (map.getMapValue(j ,i)) {
                case 0:
                    mvwaddch(stdscr, i, j, ' ' | COLOR_PAIR(1));
                    break;
                case 1:
                    mvwaddch(stdscr, i, j, '-' | COLOR_PAIR(1));
                    break;
                case 2:
                    mvwaddch(stdscr, i, j, '=' | COLOR_PAIR(1));
                    break;
                default:
                    mvwaddch(stdscr, i, j, ' ' | COLOR_PAIR(1));
                    break;
            }
        }
    }

    refresh();
    getch();
    endwin();

    return 0;
}