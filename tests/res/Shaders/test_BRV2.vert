#version 330 core

layout (location = 0) in vec4  mPos;
layout (location = 1) in vec4  mColor;
layout (location = 2) in vec2  mTexCords;
layout (location = 3) in float mTexId;

out vec4 iColor;
out vec2 texCords;
out float texId;

void main(){
    gl_Position = mPos;
    iColor = mColor;
    texCords = mTexCords;
    texId = mTexId;
}
