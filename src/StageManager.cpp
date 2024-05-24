#include <iostream>
#include <string>

#include "StageManager.h"

StageManager::StageManager() : nowStage(0), nowScore(0) {
    for (int i = 0; i < 4; ++i) {
        missionStatus[i] = 0;
        isMissionClear[i] = false;
    }
}

// 현재 스테이지의 미션 상태 배열 반환
int* StageManager::getMissionStatus() {
    return missionStatus;
}

bool StageManager::checkMissionClear() {
    bool isCleared;
    for (int i=0; i<4; i++) {
        if(isMissionClear[i]) isCleared = true;
        else {
            isCleared = false; 
            break;
        }
    }
    return isCleared;
}

// 현재 스테이지의 미션 수행 상태 갱신
void StageManager::updateMissionStatus(int missionType, int value) {
    switch(missionType) {
        case 0: missionStatus[0] += value; break;
        case 1: missionStatus[1] += value; break;
        case 2: missionStatus[2] += value; break;
        case 3: missionStatus[3] += value; break;
    }
    updateIsMissionClear();
}

void StageManager::updateIsMissionClear() {
    for(int missionType = 0; missionType < 4; ++missionType) {
        if (stage.getMission(nowStage, missionType) <= missionStatus[missionType]) {
            isMissionClear[(missionType)] = true;
        }
        else break;
    }
}

/////////////////////수정필요/////////////////
// gate 함수 구현 안 돼서 mission[3] = true로 임시 설정
// 현재 스테이지의 미션 상태 초기화
void StageManager::initNowStage(Snake& snake) {
    nowScore = 0;

    for (int i = 0; i < 4; ++i) 
        missionStatus[i] = 0;

    for (int i = 0; i < 4; ++i)
        isMissionClear[i] = false;

    missionStatus[0] = snake.getBodyLen();
    isMissionClear[3] = true;
    
}

// 접근자와 설정자
bool* StageManager::getIsMissionClear() {
    return isMissionClear;
}
void StageManager::setIsMissionClear(int missionType, bool turn) {
    isMissionClear[missionType] = turn;
}

int StageManager::getNowScore() {
    return nowScore;
}

void StageManager::setNowScore(int score) {
    nowScore = score;
}
 
void StageManager::updateNowScore(Snake& snake, int scoreType) {
    switch(scoreType) {
        case 0: // 뱀의 몸 길이
            nowScore = snake.getBodyLen() / snake.maxBodyLen() * 10;
            break;
        case 1: // growth
            nowScore += (nowStage+1)*2;
            break;
        case 2: // poisn
            nowScore += (nowStage+1);
            break;
        case 3: // gate
            nowScore += (nowStage+1)*3;
            break;
        default:
            break;
    }
}

int StageManager::getNowStage() {
    return nowStage;
}
void StageManager::setNowStage() {
    nowStage++;
}