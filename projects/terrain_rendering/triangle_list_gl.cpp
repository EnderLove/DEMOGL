#include "../../core/math3D.h"
#include "triangle_list_gl.h"
#include "terrain.h"
#include <cassert>

void TriangleList::CreateTriangleList(int width, int depth, const BaseTerrain* terrain){
    width_ = width;
    depth_ = depth;

    CreateGLState();
    PopulateBuffers(terrain);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TriangleList::CreateGLState(){
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);

    int POS_LOC = 0;
    glEnableVertexAttribArray(POS_LOC);

    size_t floatNum = 0;
    glVertexAttribPointer(POS_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(floatNum * sizeof(float)));
    floatNum += 3;
}

void TriangleList::PopulateBuffers(const BaseTerrain* terrain){
    std::vector<Vertex> vertices;
    vertices.resize(width_ * depth_);
    
    InitVertices(terrain, vertices);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
}

void TriangleList::Vertex::InitVertex(const BaseTerrain* terrain, int x, int z){
    pos = Vec3f(x, 0.0f, z);
}

void TriangleList::InitVertices(const BaseTerrain *terrain, std::vector<Vertex> &vertices){
    int index = 0;

    for (int z = 0; z < depth_; z++){
        for (int x = 0; x < width_; x++){
            assert(index < vertices.size());
            vertices[index].InitVertex(terrain, x, z);
            index++;
        }
    }
}

void TriangleList::Render(){
    glBindVertexArray(VAO_);
    glDrawArrays(GL_POINTS, 0, depth_ * width_);
    glBindVertexArray(0);
}
