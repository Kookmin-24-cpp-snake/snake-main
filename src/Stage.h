#ifndef __STAGE__
#define __STAGE__

#include <array>

class Stage {
private:
    std::array<std::array<int, 4>, 4> mission;

public:
    Stage();
    
    int getMission(int nowStage, int missionType) const;
    const std::array<int, 4>& getMission(int nowStage) const;
};

#endif
 