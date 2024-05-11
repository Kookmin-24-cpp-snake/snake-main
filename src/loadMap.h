/**
 * @file loadMap.h
 * @author hyeoksu
 * @brief 
 * map�� �о���� �Լ��� ����
 * @date 2024-05-11
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
 * @brief 
 * map.txt ������ �о���� string type���� ��ȯ�Ѵ�.
 * @return string 
 */
string mapRead(){
    string total;
    ifstream file("map/map1.txt");
    
    /**
     * @brief 
     * ������ ������ ���� �о� total�� ����.
     */
    // ��ġ �����ڸ� ���� ������ �ű��.
	if(file.is_open()){	
        file.seekg(0,std::ios::end);
		
		// �׸��� �� ��ġ�� �д´�. (������ ũ��)
		int size = file.tellg();

		// �� ũ���� ���ڿ��� �Ҵ��Ѵ�.
		total.resize(size);

		// ��ġ �����ڸ� �ٽ� ���� �� ������ �ű��.
		file.seekg(0, ios::beg);

		// ���� ��ü ������ �о ���ڿ��� ����
		file.read(&total[0], size);
	}
    else{
		return "fail";
	}
    return total;
}