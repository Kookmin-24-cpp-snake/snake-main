/**
 * @file Map.cpp
 * @author hyeoksu
 * @brief 임시 class Map의 소스파일입니다.
 * @date 2024-05-18
 */

#include "Map.h"

void Map::setDirectory(const string& directory){
    this->directory = directory;
}

string Map::loadMap(){
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

void Map::setMap(){
    string mapResource = loadMap();
    map = new int*[height + 1];
    for (int i = 0; i < height + 1; i++)
        map[i] = new int[width + 1];

    for(int i = 0; i < height + 1; i++){
        for(int j = 0; j < width; j++){
            map[i][j] = mapResource[i * (width + 1) + j] - '0';
        }
    }
}

Map::~Map(){
    for (int i = 0; i < height + 1; i++)
        delete[] map[i];
    delete[] map;
}

void Map::setCoordToValue(int x, int y, int value) {
    if (x >= 0 && x <= width && y >= 0 && y <= height) {
        map[y][x] = value;
    }
}

int Map::getMapValue(int x, int y){
    return map[y][x];
}

int Map::getHeight(){
    return this->height;
}

int Map::getWidth(){
    return this->width;
}