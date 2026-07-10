#ifndef MIDPOINT_DISP_H
#define MIDPOINT_DISP_H

#include "terrain.h"

class MidpointDisp : public BaseTerrain{
private:
    float minHeight_;
    float maxHeight_;

    void CreateMidpointDisplacementF32(float roughness);
    void DiamontStep(int rectSize, float curHeight);
    void SquareStep (int rectSize, float curHeight);

public:
    void CreateMidpointDisplacement(int terrainSize, float roughness, float minHeight, float maxHeight);

};

#endif // MIDPOINT_DISP_H!
