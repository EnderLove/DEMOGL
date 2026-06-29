#ifndef TERRAIN_H
#define TERRAIN_H

#include "../../core/utils.h"
#include "../../core/array2D.h"
#include "../../core/basicCamera.h"
#include "../../core/shader.h"
#include "triangle_list_gl.h"

class BaseTerrain{
public:
    BaseTerrain(){}
    void InitTerrain(float worldScale);
    void Render(const BasicCamera &camera);
    void LoadFromFile(const char* filename);

    float GetHeightFromMapCoord(int x, int z) const { return heightMap_.Get(x, z); }
    float GetWorldScale() const { return worldScale_; }
    
protected:
    int terrainSize_ = 0;
    float worldScale_ = 1.0f;
    Array2D<float> heightMap_;
    TriangleList triangleList_;
    Shader terrainShader;

    void LoadHeightMapFile(const char* filename);
};

#endif // TERRAIN_H!
