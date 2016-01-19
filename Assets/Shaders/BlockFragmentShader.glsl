#version 430 core
uniform vec4 uColor;

void main()
{
	gl_FragColor.r = 0.1f;
	gl_FragColor.g = 1.0f;
	gl_FragColor.b = 0.6;
	gl_FragColor.a = 0.6;
}