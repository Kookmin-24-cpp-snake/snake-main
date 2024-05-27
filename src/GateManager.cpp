#include "GateManager.h"

GateManager::GateManager(Map& map) : map(map), gateSeed(0){
    srand(static_cast<unsigned int>(time(NULL)));
}

void GateManager::GateToMap(const Gate& gate){
    map.setCoordToValue(gate.getCoord().getX(), gate.getCoord().getY(), GATE);
}

void GateManager::GateDelete(const Gate& gate) {
    map.setCoordToValue(gate.getCoord().getX(), gate.getCoord().getY(), 0);
}

int GateManager::GateStatus(const Gate& gate) {
    Pos coord = gate.getCoord();
    return map.getMapValue(coord.getX(), coord.getY());
}

Gate GateManager::GateMake() {
    int random, x, y;
        int h = map.getHeight();
        int w = map.getWidth();
        std::vector<std::pair<int, int>> emptyPositions;

        // 모든 벽 위치 수집
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (map.getMapValue(i, j) == 1) {
                    emptyPositions.push_back(std::make_pair(i, j));
                }
            }
        }

        // 무작위로 벽 위치 선택
        std::pair<int, int> pos = emptyPositions[rand() % emptyPositions.size()];
        x = pos.first;
        y = pos.second;

        random = rand() % 2;
        gateSeed += 1; // 시드 증가 (다른 곳에서 필요할 경우를 대비)

        return Gate(x, y);
}

Pos GateManager::getGateCoord(const Gate& gate) {
    return gate.getCoord();
}