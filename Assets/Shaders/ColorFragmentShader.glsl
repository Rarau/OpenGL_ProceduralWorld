#version 430 core
uniform vec4 uColor;
layout(location = 3) uniform sampler2DArray uTextureArray;

void main()
{
	gl_FragColor = texture(uTextureArray, vec3(0.5, 0.1, 21));
}