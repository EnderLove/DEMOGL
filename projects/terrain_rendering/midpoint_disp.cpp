#include "midpoint_disp.h"
#include "math3D.h"
#include <cmath>
#include <cstdlib>

void MidpointDisp::CreateMidpointDisplacement(int terrainSize, float roughness, float minHeight, float maxHeight){
    if (roughness < 0.0f){
        printf("%s: roughness must be positive - %f\n", __FUNCTION__, roughness);
        exit(0);
    }

    terrainSize_ = terrainSize;
    minHeight_ = minHeight;
    maxHeight_ = maxHeight;

    terrainShader.use();
    terrainShader.setFloat("minHeight", minHeight_);
    terrainShader.setFloat("maxHeight", maxHeight_);

    heightMap_.InitArray2D(terrainSize_, terrainSize_, 0.0f);

    CreateMidpointDisplacementF32(roughness);

    heightMap_.Normalize(minHeight_, maxHeight_);

    triangleList_.CreateTriangleList(terrainSize_, terrainSize_, this);
}

void MidpointDisp::CreateMidpointDisplacementF32(float roughness){
    int rectSize = cpm::CalcNextPowerOfTwo(terrainSize_);
    float curHeight = (float)rectSize / 2.0f;
    float heightReduce = pow(2.0f, -roughness);

    while (rectSize > 0){
        DiamondStep(rectSize, curHeight);
        SquareStep (rectSize, curHeight);

        rectSize  /= 2;
        curHeight *= heightReduce;
    }
}

void MidpointDisp::DiamondStep(int rectSize, float curHeight){
    int halfRectSize = rectSize / 2;

    for (int y = 0; y < terrainSize_; y += rectSize){
        for (int x = 0; x < terrainSize_; x += rectSize){
            int next_x = (x + rectSize) % terrainSize_;
            int next_y = (y + rectSize) % terrainSize_;

            if (next_x < x) next_x = terrainSize_ - 1;
            if (next_y < y) next_y = terrainSize_ - 1;

            float topLeft     = heightMap_.Get(x, y);
            float topRight    = heightMap_.Get(next_x, y);
            float bottomLeft  = heightMap_.Get(x, next_y);
            float bottomRight = heightMap_.Get(next_x, next_y);

            int mid_x = (x + halfRectSize) % terrainSize_;
            int mid_y = (y + halfRectSize) % terrainSize_;

            float randValue = cpm::RandomFloatRange(-curHeight, curHeight);
            float midPoint = (topLeft + topRight + bottomLeft + bottomRight) / 4.0f;

            heightMap_.Set(mid_x, mid_y, midPoint + randValue);
        }
    }
}

void MidpointDisp::SquareStep(int rectSize, float curHeight){
    int halfRectSize = rectSize / 2;

    for (int y = 0; y < terrainSize_; y += rectSize){
        for (int x = 0; x < terrainSize_; x += rectSize){
            int next_x = (x + rectSize) % terrainSize_;
            int next_y = (y + rectSize) % terrainSize_;

            if (next_x < x) next_x = terrainSize_ - 1;
            if (next_y < y) next_y = terrainSize_ - 1;

            int mid_x = (x + halfRectSize) % terrainSize_;
            int mid_y = (y + halfRectSize) % terrainSize_;

            int prevMid_x = (x - halfRectSize + terrainSize_) % terrainSize_;
            int prevMid_y = (y - halfRectSize + terrainSize_) % terrainSize_;

            float curTopLeft  = heightMap_.Get(x, y);
            float curTopRight = heightMap_.Get(next_x, y);
            float curCenter   = heightMap_.Get(mid_x, mid_y);
            float prevYCenter = heightMap_.Get(mid_x, prevMid_y);
            float curBotLeft  = heightMap_.Get(x, next_y);
            float prevXCenter = heightMap_.Get(prevMid_x, mid_y);

            float curLeftMid = (curTopLeft + curCenter + curBotLeft  + prevXCenter) / 4.0f + cpm::RandomFloatRange(-curHeight, curHeight);
            float curTopMid  = (curTopLeft + curCenter + curTopRight + prevYCenter) / 4.0f + cpm::RandomFloatRange(-curHeight, curHeight);

            heightMap_.Set(mid_x, y, curTopMid);
            heightMap_.Set(x, mid_y, curLeftMid);
        }
    }
}

