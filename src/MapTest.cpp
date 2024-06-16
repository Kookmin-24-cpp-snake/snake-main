/**
 * @file MapTest.cpp
 * @author hyeoksu
 * @brief Map 클래스가 정상 작동하는지 확인하는 코드입니다.
 * make MapTest로 실행 가능합니다.
 * @date 2024-05-18
 */
#include <ncurses.h>
#include "Map.h"

void tmpRender(Map& map);
void setDirectory(int stageNum, Map& map);
void nextOrStop();

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    noecho();
    curs_set(0);
    
    Map map;
    for (int i = 1; i < 5; i++){
        setDirectory(i, map);
        map.setMap();
        tmpRender(map);
        nextOrStop();
    }
    delwin(stdscr);
    endwin();
    return 0;
}

void tmpRender(Map& map){
    for (int i = 0; i < map.getHeight(); i++) {
        for (int j = 0; j < map.getWidth(); j++) {
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
}

void setDirectory(int stageNum, Map& map){
    switch(stageNum){
            case 1:
            map.setDirectory("map/map1.txt");
            break;
            case 2:
            map.setDirectory("map/map2.txt");
            break;
            case 3:
            map.setDirectory("map/map3.txt");
            break;
            case 4:
            map.setDirectory("map/map4.txt");
            break;
        }
}

void nextOrStop(){
    mvprintw(15, 26, "Press n to display the next map");
    mvprintw(16, 26, "Press q to quit");
    int ch;
    while(true){
        ch = getch();
        if (ch != ERR) {
            if (ch == 'n' || ch == 'N') {
                break;
            } else if(ch == 'q' || ch == 'Q'){
                delwin(stdscr);
                endwin();
                exit(0);
            }
        }
    }
}