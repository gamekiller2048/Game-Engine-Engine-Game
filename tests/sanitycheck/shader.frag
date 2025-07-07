#version 430 core

uniform sampler2D u_tex;
in vec2 texUV;

void main()
{
    gl_FragColor = texture(u_tex, texUV);
}