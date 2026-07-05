#ifndef FAULT_FORMATION_H
#define FAULT_FORMATION_H

#include "terrain.h"

class FaultFormation : public BaseTerrain{
private:
    struct TerrainPoint{
        int x = 0;
        int z = 0;

        void Print(){ printf("[%d, %d]", x, z); }
        bool IsEqual(TerrainPoint &p) const { return ((x == p.x) && (z == p.z)); }
    };

    float minHeight_ = 0;
    float maxHeight_ = 0;

    void CreateFaultFormationInternal(int Iterations, float MinHeight, float MaxHeight);
    void GenRandomTerrainPoints(TerrainPoint &p1, TerrainPoint &p2);

public:
    FaultFormation(){}
    void CreateFaultFormation(int TerrainSize, int Iterations, float MinHeight, float MaxHeight);
};

#endif // FAULT_FORMATION_H!
