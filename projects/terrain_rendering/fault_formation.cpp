#include "fault_formation.h"
#include <cstdlib>

void FaultFormation::CreateFaultFormation(int TerrainSize, int Iterations, float MinHeight, float MaxHeight, float Filter){
    terrainSize_ = TerrainSize;
    minHeight_ = MinHeight; 
    maxHeight_ = MaxHeight;

    terrainShader.use();
    terrainShader.setFloat("maxHeight", maxHeight_);
    terrainShader.setFloat("minHeight", minHeight_);

    heightMap_.InitArray2D(TerrainSize, TerrainSize, 0.0f);

    CreateFaultFormationInternal(Iterations, minHeight_, maxHeight_, Filter);

    heightMap_.Normalize(minHeight_, maxHeight_);

    triangleList_.CreateTriangleList(TerrainSize, TerrainSize, this);
}

void FaultFormation::CreateFaultFormationInternal(int Iterations, float MinHeight, float MaxHeight, float Filter){
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
    SetFIRFilter(Filter);
}

void FaultFormation::SetFIRFilter(float filter){
    // LEFT TO RIGHT 
    for (int z = 0; z < terrainSize_; z++){
        float prevVal = heightMap_.Get(0, z);
        for (int x = 1; x < terrainSize_; x++){
            prevVal = FIRFilterSinglePoint(x, z, prevVal, filter);
        }
    }
    // RIGHT TO LEFT  
    for (int z = 0; z < terrainSize_; z++){
        float prevVal = heightMap_.Get(terrainSize_ - 1, z);
        for (int x = terrainSize_ - 2; x >= 0; x--){
            prevVal = FIRFilterSinglePoint(x, z, prevVal, filter);
        }
    }
    // LEFT TO RIGHT 
    for (int x = 0; x < terrainSize_; x++){
        float prevVal = heightMap_.Get(x, 0);
        for (int z = 1; z < terrainSize_; z++){
            prevVal = FIRFilterSinglePoint(x, z, prevVal, filter);
        }
    }
    // LEFT TO RIGHT 
    for (int x = 0; x < terrainSize_; x++){
        float prevVal = heightMap_.Get(x, terrainSize_ - 1);
        for (int z = terrainSize_ - 2; z >= 0; z--){
            prevVal = FIRFilterSinglePoint(x, z, prevVal, filter);
        }
    }
}

float FaultFormation::FIRFilterSinglePoint(int x, int z, float prevVal, float filter){
    float currentVal = heightMap_.Get(x, z);
    float newVal = filter * prevVal + (1 - filter) * currentVal;
    heightMap_.Set(x,z,newVal);
    return newVal;
}

void FaultFormation::GenRandomTerrainPoints(TerrainPoint &p1, TerrainPoint &p2){
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
