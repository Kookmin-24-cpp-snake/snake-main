/**
 * @file loadMap.h
 * @author hyeoksu
 * @brief 
 * map을 읽어오는 함수의 원형
 * @date 2024-05-11
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
 * @brief 
 * map.txt 파일을 읽어오고 string type으로 반환한다.
 * @return string 
 */
string mapRead(){
    string total;
    ifstream file("map/map1.txt");
    
    /**
     * @brief 
     * 파일의 내용을 전부 읽어 total에 저장.
     */
    // 위치 지정자를 파일 끝으로 옮긴다.
	if(file.is_open()){	
        file.seekg(0,std::ios::end);
		
		// 그리고 그 위치를 읽는다. (파일의 크기)
		int size = file.tellg();

		// 그 크기의 문자열을 할당한다.
		total.resize(size);

		// 위치 지정자를 다시 파일 매 앞으로 옮긴다.
		file.seekg(0, ios::beg);

		// 파일 전체 내용을 읽어서 문자열에 저장
		file.read(&total[0], size);
	}
    else{
		return "fail";
	}
    return total;
}