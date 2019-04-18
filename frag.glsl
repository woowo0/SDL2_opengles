#version 300 es

precision highp float;

// Ouput data
out vec3 color;

void main()
{
	color[0] = gl_FragCoord.x/1080.0;
	color[1] = gl_FragCoord.y/1920.0;
	color[2] = 0.5;
}
