#version 430 core
uniform vec4 uColor;

in vec4 vColor;

void main()
{
	gl_FragColor.r = vColor.r;
	gl_FragColor.g = 0.1;
	gl_FragColor.b = 0.1;
	gl_FragColor.a = 0.1;
}