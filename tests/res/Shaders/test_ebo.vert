#version 330 core
layout (location = 0) in vec4 aPos;

uniform vec4 iColor;
out vec4 mColor;

void main(){
    gl_Position = aPos;
    mColor = iColor;
}
