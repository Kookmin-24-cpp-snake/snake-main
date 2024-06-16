#include "Stage.h"

Stage::Stage() {
    mission[0] = {4, 1, 0, 0};
    mission[1] = {4, 1, 0, 0};
    mission[2] = {4, 1, 0, 0};
    mission[3] = {4, 1, 0, 0};

    // mission[0] = {4, 2, 1, 1};
    // mission[1] = {5, 3, 2, 2};
    // mission[2] = {6, 4, 3, 3};
    // mission[3] = {7, 5, 4, 4};

}

int Stage::getMission(int nowStage, int missionType) const {
    return mission[nowStage][missionType];
}

const std::array<int, 4>& Stage::getMission(int nowStage) const {
    return mission[nowStage];
}
