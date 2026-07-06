#ifndef TERRAIN_H
#define TERRAIN_H
 
#include "utils.h"
#include "array2D.h"
#include "math3D.h"
#include "basicCamera.h"
#include "camera.h"
#include "shader.h"

#include "triangle_list_gl.h"

class BaseTerrain{
public:
    BaseTerrain(){}
    ~BaseTerrain();

    void Destroy();
    void InitTerrain(float worldScale);      // Initialize the shaders and the scale of the world
    void Render(const Camera &camera);       // Gets the camera and takes the matrix for rendering
    void LoadFromFile(const char* filename); // Calls the LoadHeightMapFile() and CreateTriangleList

    // Gets the true coord from the heightMap
    float GetHeightFromMapCoord(int x, int z) const { return heightMap_.Get(x, z); }
    // Gets the world scale value 
    float GetWorldScale() const { return worldScale_; }
    
protected:
    int            terrainSize_ = 0;
    float          worldScale_  = 1.0f;
    Array2D<float> heightMap_;
    TriangleList   triangleList_;
    Shader         terrainShader;

    void LoadHeightMapFile(const char* filename); // Reads the file, loads the buffer and initialize the Array2D
};

#endif // TERRAIN_H!
