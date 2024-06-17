/**
 * @file Map.cpp
 * @author hyeoksu
 * @date 2024-05-18
 */

#include "Map.h"

void Map::setDirectory(const std::string& directory){
    this->directory = directory;
}

std::string Map::loadMap(){
    std::string total;
    std::ifstream file(directory);

    /**
     * @brief 
     * 파일의 내용을 전부 읽어 total에 저장.
     */
	if(file.is_open()){
        file.seekg(0, std::ios::end);
		
		int size = file.tellg();

		total.resize(size);

		file.seekg(0, std::ios::beg);

		file.read(&total[0], size);
	}
    else{
		return "fail";
	}
    return total;
}

std::string Map::getStageDirectory(int stage) {
    switch (stage) {
        case 1:
            return "map/map1.txt";
        case 2:
            return "map/map2.txt";
        case 3:
            return "map/map3.txt";
        case 4:
            return "map/map4.txt";
        default:
            return "map/map1.txt";
    }
}

void Map::setMap(){
    std::string mapResource = loadMap();
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

std::vector<std::pair<int, int>> Map::emptyCoords(){
    std::vector<std::pair<int, int>> emptyPositions;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (getMapValue(i, j) == 0) {
                emptyPositions.push_back(std::make_pair(i, j));
            }
        }
    }

    return emptyPositions;
}

std::vector<std::pair<int, int>> Map::wallCoords(){
    std::vector<std::pair<int, int>> wallPositions;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (getMapValue(i, j) == 1) {
                wallPositions.push_back(std::make_pair(i, j));
            }
        }
    }

    return wallPositions;
}