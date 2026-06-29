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
    void InitTerrain();
    void Render(const BasicCamera &camera);
    void LoadFromFile(const char* filename);

protected:
    int terrainSize_ = 0;
    Array2D<float> heightMap_;
    TriangleList triangleList_;
    Shader terrainShader;

    void LoadHeightMapFile(const char* filename);
};

#endif // TERRAIN_H!
