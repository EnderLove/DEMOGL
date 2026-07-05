#include "fault_formation.h"
#include <cstdlib>
#include <sched.h>

FaultFormation::CreateFaultFormation(int TerrainSize, int Iterations, float MinHeight, float MaxHeight){
    terrainSize_ = TerrainSize;
    minHeight_ = MinHeight; 
    maxHeight_ = MaxHeight;

    heightMap_.InitArray2D(TerrainSize, TerrainSize, 0.0f);

    CreateFaultFormationInternal(Iterations, minHeight_, maxHeight_);

    heightMap_.Normalize(minHeight_, maxHeight_);

    triangleList_.CreateTriangleList(TerrainSize, TerrainSize, this);
}

FaultFormation::CreateFaultFormationInternal(int Iterations, float MinHeight, float MaxHeight){
    float deltaHeight = MaxHeight - MinHeight;

    for (int i = 0; i < Iterations; i++){
        float itRatio = ((float)i / (float)Iterations);
        float height = MinHeight - itRatio * deltaHeight;

        TerrainPoint p1, p2;

        GenRandomTerrainPoints(p1, p2);

        int dirX = p2.x - p1.x;
        int dirZ = p2.z - p1.z;

        for (int x = 0; x < terrainSize_; x++){
            for (int z = 0; z < terrainSize_; z++){
                int toPointDirX = x - p1.x;
                int toPointDirZ = z - p1.z;

                int cross = toPointDirX * dirZ - toPointDirZ * dirX;

                if (cross > 0){
                    float curHeight = heightMap_.Get(x, z);
                    heightMap_.Set(x, z, curHeight + height);
                }
            }
        }
    }
}

FaultFormation::GenRandomTerrainPoints(TerrainPoint &p1, TerrainPoint &p2){
    p1.x = rand() % terrainSize_;
    p1.z = rand() % terrainSize_;

    int counter = 0;

    do{
        p2.x = rand() % terrainSize_;
        p2.z = rand() % terrainSize_;

        if (counter++ == 1000){
            printf("Endless loop detected in %s: %d\n", __FILE__, __LINE__);
            assert(0);
        }
    } while (p1.IsEqual(p2));
}
