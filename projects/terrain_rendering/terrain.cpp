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
    int fileSize = 0; // This value is taken as reference by the ReadBinaryFile
    unsigned char* contentBuffer = (unsigned char*)ReadBinaryFile(filename, fileSize); 
    
    assert(fileSize % sizeof(float) == 0);

    terrainSize_ = std::sqrt(fileSize / sizeof(float));

    heightMap_.InitArray2D(terrainSize_, terrainSize_, contentBuffer);
    //heightMap_.PrintFloat();
}

void BaseTerrain::Render(const Camera &camera){
    cpm::Mat4 matView = camera.GetViewMatrix();
    cpm::Mat4 matProj = camera.GetProjMatrix(); 

    cpm::Mat4 viewProjection = matProj * matView;
    terrainShader.use();
    terrainShader.setMat4("ViewProjection", viewProjection);
    
    triangleList_.Render();
}
