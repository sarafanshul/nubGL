#version 330 core
layout (location = 0) in vec4 pos;

out vec4 color ;

void main() {
    gl_Position = pos ;
    color = vec4( 0.2, 0.3, 0.9, 0.9 );
}
