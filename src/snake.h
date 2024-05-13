/**
 * @file snake.h
 * @author hyeoksu
 * @brief 
 * @date 2024-05-11
 */

#include <iostream>
#include <vector>
#include <ncurses.h>
using namespace std;
class snake{
public:
    int x, y;
    int min_length=3;
    char readingMap[23][23];
    vector <pair<int,int>> body;
    snake(int y,int x);
    void showMap(WINDOW* w, char* map);
    void showSnake();
};