/**
 * @file Map.h
 * @author hyeoksu
 * @brief 
 * ItemManager 구현을 위해 임시로 만든 Map의 헤더파일입니다.
 * @date 2024-05-18
 */
#ifndef __MAP__
#define __MAP__
#include <string>
#include <fstream>
using namespace std;

class Map{
    const int height= 22, width = 22;
    int** map;
    string directory;
public:
    ~Map();
    void setDirectory(const string& directory);
    string loadMap();
    void setMap(const string& mapResource);
    void setCoordToValue(int x, int y, int value);
    int getMapValue(int x, int y);
    int getHeight();
    int getWidth();
};
#endif