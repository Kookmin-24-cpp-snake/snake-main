/**
 * @file showMap.cpp
 * @author hyeoksu
 * @brief
 * map.txt 파일을 불러와 ncurses를 통해 창에 표현
 * @date 2024-05-11
 * 
 * 
 */
#include <ncurses.h>
#include "loadMap.h"
using namespace std;

int main(){
    string mapResource = mapRead();
    // 2차원배열로 바꾸는게 snake 표시에 더 유용하다 판단, 코드 수정했습니다.
    char readingMap[23][23];
    for(int i=0;i<23;i++){
        for(int j=0;mapResource[i*23+j]!='\0';j++){
            readingMap[i][j]=mapResource[i*23+j];
        }
    }
    initscr();
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    for(int i = 0; i < 23; i++){
      for(int j = 0; j < 23; j++){
        switch(readingMap[i][j]){
            case '0':
            mvwaddch(stdscr, i, j, ' '|COLOR_PAIR(1));
            break;
            case '1':
            mvwaddch(stdscr, i, j, '-'|COLOR_PAIR(1));
            break;
            case '2':
            mvwaddch(stdscr, i, j, '='|COLOR_PAIR(1));
            break;
        }
      }
    }
    refresh();
    getch();
    endwin();
}