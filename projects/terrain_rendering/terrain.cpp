#include "terrain.h"
#include <cassert>
#include <cmath>

#include "terrain.h"

void BaseTerrain::InitTerrain(float worldScale){
    worldScale_ = worldScale;
    terrainShader.SetFiles("../../../projects/terrain_rendering/terrain.vert", "../../../projects/terrain_rendering/terrain.frag");
}

void BaseTerrain::LoadFromFile(const char* filename){
    LoadHeightMapFile(filename);

    triangleList_.CreateTriangleList(terrainSize_, terrainSize_, this);
}

void BaseTerrain::LoadHeightMapFile(const char* filename){
    int fileSize = 0;
    unsigned char* contentBuffer = (unsigned char*)ReadBinaryFile(filename, fileSize); 
    
    assert(fileSize % sizeof(float) == 0);

    terrainSize_ = std::sqrt(fileSize / sizeof(float));

    heightMap_.InitArray2D(terrainSize_, terrainSize_, contentBuffer);
    //heightMap_.PrintFloat();
}

void BaseTerrain::Render(const BasicCamera &camera){
    Mat4 viewProjection = camera.GetViewProjMatrix();
    
    terrainShader.use();
    terrainShader.setMat4("ViewProjection", viewProjection);
    
    triangleList_.Render();
}
