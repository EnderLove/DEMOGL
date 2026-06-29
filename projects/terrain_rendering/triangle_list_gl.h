#ifndef TRIANGLE_LIST_GL_H
#define TRIANGLE_LIST_GL_H

#include <vector>

#include "../../vendor/glad/glad.h"
#include "../../core/math3D.h"

class BaseTerrain;

class TriangleList{
private: 
    int width_ = 0;
    int depth_ = 0;
    GLuint VAO_;
    GLuint VBO_;
    GLuint IBO_;

    struct Vertex{
        Vec3f pos;
        void InitVertex(const BaseTerrain* terrain, int x, int z);
    };

public:
    TriangleList(){}

    void CreateTriangleList(int width, int depth, const BaseTerrain* terrain);
    void CreateGLState();
    void PopulateBuffers(const BaseTerrain* terrain);
    void InitVertices(const BaseTerrain *terrain, std::vector<Vertex> &vertices);
    void InitIndices(std::vector<unsigned int> &indices);
    void Render();

};

#endif // TRIANGLE_LIST_GL_H!
