#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 v_TexCoord;
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

void main(){
//    vec4 texColor = mix( texture(u_Texture0, v_TexCoord), texture(u_Texture1, v_TexCoord), 0.5 );
    vec4 t0 = texture(u_Texture0, v_TexCoord);
    vec4 t1 = texture(u_Texture1, v_TexCoord);

    vec4 texColor = t0 + t1 * (1 - t0.a);
    FragColor = texColor ;
}
