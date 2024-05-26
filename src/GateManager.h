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
#include "Map.h"

#ifndef __GSEED__
#define __GSEED__
extern int gateSeed; // seed값으로 사용할 int type 전역 변수
#endif

class GateManager{
    Map& map;
public:
    GateManager(Map& map);
    void GateToMap(const Gate& gate);
    void GateDelete(const Gate& gate);
    int GateStatus(const Gate& gate);
    Gate GateMake();
    Pos getGateCoord(const Gate& gate);
};
#endif