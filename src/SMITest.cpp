/**
 * @file SMITest.cpp
 * @author hyeoksu
 * @brief Snake와 Item을 Map 위에 출력하는 프로그램입니다.
 * make SMItest로 실행 가능합니다.
 * @date 2024-05-18
 */
#include <ncurses.h>
#include "Item.h"
#include "Snake.h"
#include "Map.h"
#include "ItemManager.h"

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    Map map;
    map.setDirectory("map/map1.txt");
    map.setMap();

    Snake snake(Pos(10, 10), 3, UP);
    map.setCoordToValue(10, 10, 3);
    map.setCoordToValue(10, 11, 4);
    map.setCoordToValue(10, 12, 4);

    ItemManager iM(map);
    Item item = iM.itemMake();
    map.setCoordToValue(item.getCoord().getX(), item.getCoord().getY(), item.getType());

    int height = map.getHeight();
    int width = map.getWidth();
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            switch (map.getMapValue(j, i)) {
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
    getch();
    endwin();
    return 0;
}
