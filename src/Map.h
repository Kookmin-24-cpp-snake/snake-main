/**
 * @file Map.h
 * @author hyeoksu
 * @brief 
 * @date 2024-05-18
 */
#ifndef __MAP__
#define __MAP__
#include <string>
#include <fstream>
#include <vector>

class Map{
    const int height= 22, width = 22;
    int** map;
    std::string directory;
public:
    ~Map();
    void setDirectory(const std::string& directory);
    std::string loadMap();
    std::string getStageDirectory(int stage);
    void setMap();
    void setCoordToValue(int x, int y, int value);
    int getMapValue(int x, int y);
    int getHeight();
    int getWidth();
    std::vector<std::pair<int, int>> emptyCoords();
    std::vector<std::pair<int, int>> wallCoords();
};
#endif