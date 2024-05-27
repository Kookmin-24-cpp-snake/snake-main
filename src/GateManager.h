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
    int gateSeed;
public:
    GateManager(Map& map);
    void GateToMap(const Gate& gate);
    void GateDelete(const Gate& gate);
    int GateStatus(const Gate& gate);
    Gate GateMake();
    Pos getGateCoord(const Gate& gate);
};
#endif