#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 color; // output color

uniform float scale = 1.0; // never declare unused uniforms.

void main(){
    gl_Position = vec4(
        aPos.x * scale,
        aPos.y * scale,
        aPos.z * scale,
        1.0
    );
    color = aColor;
}
