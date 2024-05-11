/**
 * @file showMap.cpp
 * @author hyeoksu
 * @brief
 * map.txt ������ �ҷ��� ncurses�� ���� â�� ǥ��
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