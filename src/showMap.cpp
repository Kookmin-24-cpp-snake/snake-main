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
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
 * @brief 
 * map.txt 파일을 읽어오고 string type으로 반환한다.
 * @return string 
 */
string loadMap(string& directory){
    string total;
    ifstream file(directory);
  
    /**
     * @brief 
     * 파일의 내용을 전부 읽어 total에 저장.
     */
	if(file.is_open()){
		//위치 지정자를 파일 끝으로 옮긴다.
        file.seekg(0, ios::end);
		
		// 그리고 그 위치를 읽는다. (파일의 크기)
		int size = file.tellg();

		// 그 크기의 문자열을 할당한다.
		total.resize(size);

		// 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
		file.seekg(0, ios::beg);

		// 파일 전체 내용을 읽어서 문자열에 저장
		file.read(&total[0], size);
	}
    else{
		return "fail";
	}
    return total;
}

void showMap(){
    string map1="map/map1.txt";
    string mapResource = loadMap(map1);
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
            case '3':
            mvwaddch(stdscr, i, j, 'H'|COLOR_PAIR(1));
            break;
            case '4':
            mvwaddch(stdscr, i, j, 'T'|COLOR_PAIR(1));
            break;
        }
      }
    }
    refresh();
    getch();
    endwin();
}