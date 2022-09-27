#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 v_TexCoord;
uniform sampler2D u_Texture0;
uniform vec4 t0_Color;

void main(){
    vec4 t0 = texture(u_Texture0, v_TexCoord);

    vec4 texColor = t0 + t0_Color * (t0.a); // color not comming.
    FragColor = texColor;
}
