#include "GateManager.h"

GateManager::GateManager(Map& map) : map(map){
    srand(static_cast<unsigned int>(time(NULL)));
}

void GateManager::GateToMap(const Gate& gate){
    map.setCoordToValue(gate.getCoord().getX(), gate.getCoord().getY(), GATE);
}

void GateManager::GateDelete(const Gate& gate) {
    map.setCoordToValue(gate.getCoord().getX(), gate.getCoord().getY(), 1);
}

Gate GateManager::GateMake() {
    int x, y;
        int h = map.getHeight();
        int w = map.getWidth();
        std::vector<std::pair<int, int>> wallPositions = map.wallCoords();

        // 무작위로 벽 위치 선택
        std::pair<int, int> pos = wallPositions[rand() % wallPositions.size()];
        x = pos.first;
        y = pos.second;

        return Gate(x, y);
}

Coord GateManager::getGateCoord(const Gate& gate) {
    return gate.getCoord();
}