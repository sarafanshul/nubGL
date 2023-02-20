#version 330 core

in vec4 iColor;
in vec2 texCords;
in float texId;

uniform sampler2D mTextures[3];

out vec4 FragColor;

void main(){
    int index = int(texId);
    FragColor = texture(mTextures[index], texCords);
}
