#ifndef __STAGEMANAGER__
#define __STAGEMANAGER__

#include "Stage.h"
#include "Snake.h"
#include "Map.h"
#include "Item.h"
#include "ItemManager.h"

class StageManager {
private :
    int nowScore; 
    int nowStage; 
    int playTime = 0;


    int missionStatus[4]; 
    bool isMissionClear[4]; 

    Stage stage;
public :
    StageManager();

    int getNowStage();
    int getMission(int missionType) {
        return stage.getMission(nowStage, missionType);
    }
    void setNowStage();
    void setNowStage(int s);

    int* getMissionStatus();
    bool checkMissionClear();
    void updateMissionStatus(int missionType, int value);

    bool* getIsMissionClear();
    void setIsMissionClear(int missionType, bool turn);
    void updateIsMissionClear();

    void initNowStage(Snake& snake);

    int getNowScore();
    void setNowScore(int score);
    void updateNowScore(Snake& snake, int scoreType);
    void initPlayTime();
    int getPlayTime();

};
#endif