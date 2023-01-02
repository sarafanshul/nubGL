#version 330 core

out vec4 FragColor;

in vec2 v_TexCoord;
uniform sampler2D u_Texture0;

void main(){
    vec4 t0 = texture(u_Texture0, v_TexCoord);

    FragColor = t0;
}
