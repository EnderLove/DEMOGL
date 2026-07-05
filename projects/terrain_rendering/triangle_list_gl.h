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
        cpm::Vec3f pos;
        // Uses the x and y values to get the height from the map to set the pos
        void InitVertex(const BaseTerrain* terrain, int x, int z);
    };

public:
    TriangleList(){}

    void CreateTriangleList(int width, int depth, const BaseTerrain* terrain);
    void CreateGLState(); // Generates and binds the buffers, enables the vertex attribs
    void PopulateBuffers(const BaseTerrain* terrain); // Calls the InitVertices() and InitIndices()then fills the buffers
    void InitVertices(const BaseTerrain *terrain, std::vector<Vertex> &vertices); // Generates the mesh and calls the init vertex func
    void InitIndices(std::vector<unsigned int> &indices); // Generates the indices for the IBO
    void Render(); // Binds the Vertex array and draws the elements

};

#endif // TRIANGLE_LIST_GL_H!
