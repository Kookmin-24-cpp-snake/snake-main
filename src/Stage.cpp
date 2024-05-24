#include "Stage.h"

Stage::Stage() {
    mission[0] = {0, 1, 1, 0};
    mission[1] = {0, 1, 1, 0};
    mission[2] = {0, 1, 1, 0};
    mission[3] = {0, 1, 1, 0};

}

int Stage::getMission(int nowStage, int missionType) const {
    return mission[nowStage][missionType];
}

const std::array<int, 4>& Stage::getMission(int nowStage) const {
    return mission[nowStage];
}
