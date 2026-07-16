#version 330

layout (location = 0) out vec4 FragColor;

in vec4 Color;

void main(){
    //FragColor = vec4(Color.x, 0.0, 1.0 - Color.z, Color.w); 
    FragColor = Color;
}

