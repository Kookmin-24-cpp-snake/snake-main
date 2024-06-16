#include "GateManager.h"

GateManager::GateManager(Map& map) : map(map){
    srand(static_cast<unsigned int>(time(NULL)));
}

void GateManager::GateToMap(const Gate& gate){
    map.setCoordToValue(gate.getCoord().getX(), gate.getCoord().getY(), GATE);
}

void GateManager::setGatesOnMap(Gate& gate1, Gate& gate2) {
    GateToMap(gate1);
    GateToMap(gate2);
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

void GateManager::checkGateCycle(Gate& gate1, Gate& gate2) {
    time_t present = time(nullptr);
    checkGateTimeout(gate1, present);
    checkGateTimeout(gate2, present);
}

void GateManager::checkGateTimeout(Gate& gate, time_t present) {
    int timeDifference = static_cast<int>(present - gate.getTime());
    if (timeDifference > 10) {
        GateDelete(gate);
        gate = GateMake();
        GateToMap(gate);
    }
}