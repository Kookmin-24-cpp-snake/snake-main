#include "GateManager.h"

int gateSeed;

GateManager::GateManager(Map& map) : map(map){}

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
    while(true){
        time_t t = time(NULL);
        srand(t + gateSeed);
        random = rand() % 2;
        int h = map.getHeight(); int w = map.getWidth();
        x = rand() % w; y = rand() % h;
        int value = map.getMapValue(x, y);
        if (value == 1) break;
    }
    gateSeed += 1;
    return Gate(x, y);
}

Pos GateManager::getGateCoord(const Gate& gate) {
    return gate.getCoord();
}