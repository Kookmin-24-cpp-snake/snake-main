#include "snake.h"

snake::snake(int y, int x):y(y),x(x){
    for(int i=0;i<3;i++){
        body.push_back(make_pair(y, x-i));
    }
}
void snake::showSnake(){
    readingMap[body[0].first][body[0].second] = '3';
    for(int i = 1; i < body.size(); i++){
        readingMap[body[i].first][body[i].second] = '4';}
}