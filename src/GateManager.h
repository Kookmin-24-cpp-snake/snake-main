/**
 * @file GateManager.h
 * @author hyeoksu
 * @brief 
 * @date 2024-05-26
 * 
 * 
 */

#ifndef __GATEMANAGER__
#define __GATEMANAGER__
#include "Gate.h"
#include <cstdlib>
#include <vector>
#include "Map.h"

class GateManager{
    Map& map;
public:
    GateManager(Map& map);
    void GateToMap(const Gate& gate);
    void setGatesOnMap(Gate& gate1, Gate& gate2);
    void GateDelete(const Gate& gate);
    Gate GateMake();
    Coord getGateCoord(const Gate& gate);
    void checkGateCycle(Gate& gate1, Gate& gate2);
    void checkGateTimeout(Gate& gate, time_t present);
};
#endif