#version 330 core

out vec4 FragColor ;

in vec2 texCoord ;
uniform sampler2D u_Texture0;

void main(){
    FragColor = texture(u_Texture0, texCoord);
}
