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

    glGenBuffers(1, &IBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);

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

    std::vector<unsigned int> indices;

    int numQuads = (width_ - 1) * (depth_ - 1);
    indices.resize(numQuads * 6);
    InitIndices(indices);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

void TriangleList::Vertex::InitVertex(const BaseTerrain* terrain, int x, int z){
    float y = terrain->GetHeightFromMapCoord(x, z);
    
    float worldScale = terrain->GetWorldScale();
    pos = cpm::Vec3f(x * worldScale, y, z * worldScale);
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

void TriangleList::InitIndices(std::vector<unsigned int> &indices){
    int index = 0;

    for (int z = 0; z < depth_ - 1; z++){
        for (int x = 0; x < width_ - 1; x++){
            unsigned int indexBottomLeft  = (z * width_) + x;
            unsigned int indexTopLeft     = ((z + 1) * width_) + x;
            unsigned int indexTopRight    = ((z + 1) * width_) + (x + 1);
            unsigned int indexBottomRight = (z * width_) + (x + 1);

            // Adding to top left triangle 
            indices[index++] = indexBottomLeft;
            indices[index++] = indexTopLeft;
            indices[index++] = indexTopRight;
           
            // Adding to bottom right triangle
            indices[index++] = indexBottomLeft;
            indices[index++] = indexTopRight;
            indices[index++] = indexBottomRight;
            
        }
    }
}

void TriangleList::Render(){
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, (depth_ - 1) * (width_ - 1) * 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}
