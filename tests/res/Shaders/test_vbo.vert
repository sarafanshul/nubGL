#version 330 core
layout (location = 0) in vec4 pos;

uniform vec4 iColor ;

out vec4 color ;

void main() {
    gl_Position = pos ;
    color = iColor;
}
