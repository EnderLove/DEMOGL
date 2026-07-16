#version 330

layout (location = 0) in vec3 Position;

uniform mat4 ViewProjection;

uniform float minHeight;
uniform float maxHeight;

out vec4 Color;

void main(){
    gl_Position = ViewProjection * vec4(Position, 1.0);

    float deltaHeight = maxHeight - minHeight;
    float heightRatio = (Position.y - minHeight) / deltaHeight;

    //float c = heightRatio * 0.8 + 0.2;
    float c = heightRatio;

    Color = vec4(c, c, c, 1.0);
}
