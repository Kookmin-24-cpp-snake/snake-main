/**
 * @file showMap.cpp
 * @author hyeoksu
 * @brief
 * map.txt 파일을 불러와 ncurses를 통해 창에 표현
 * @date 2024-05-11
 * 
 * 
 */
#include <iostream>
#include <ncurses.h>
#include "loadMap.h"
using namespace std;

int main(){
    string mapResource = mapRead();
    initscr();
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    for(int i=0;mapResource[i]!='\0';i++){
        if(mapResource[i]=='1') addch('-'|COLOR_PAIR(1));
        else if(mapResource[i]=='2') addch('='|COLOR_PAIR(1));
        else if(mapResource[i]=='0') addch(' ');
        else addch(mapResource[i]);
    }
    refresh();
    getch();
    endwin();
}