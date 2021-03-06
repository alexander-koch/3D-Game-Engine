// shadeless.vsh
#version 120
uniform mat4 mvp;
attribute vec3 vertex;

void main(void)
{
	gl_Position = mvp * vec4(vertex, 1.0);
}