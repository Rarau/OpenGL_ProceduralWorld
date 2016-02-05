#version 430 core
uniform vec4 uColor;

layout(location = 7) uniform mat4 modelToWorld;
layout(location = 8) uniform vec3 eyePos;
layout(location = 9) uniform vec3 diffuseCol;
layout(location = 10) uniform vec3 lightDir;
layout(location = 11) uniform vec3 ambientCol;
layout(location = 12) uniform vec3 fresnelCol;
layout(location = 13) uniform float fresnelPow;


//in vec4 vColor;
in fData
{
    vec3 normal;
    vec4 vColor;
	vec4 pos;
};

void main()
{
	//vec4 ambient = vec4(0.015, 0.015, 0.015, 1.0);
	//vec4 diffuseColor = vec4(0.16, 0.31, 1.00, 1.0);
	//vec4 diffuseColor = vec4(diffCol, 1.0);
	//vec4 ambientColor = vec4(ambientCol, 1.0);
	//vec4 fresnelColor = vec4(0.10, 0.76, 1.00, 1.0);
	//vec3 lightDir = vec3(-1.0, -1.0, 0.10);
	vec3 eyeDir = (modelToWorld * pos).xyz - eyePos;
	vec3 worldNormal = normalize((modelToWorld * vec4(normal, 0.0)).xyz);

	/*
	float fZero = 0.9510;

	vec3 halfWay = normalize(lightDir + eyeDir); //Halfway vector
	float base = 1-dot(eyeDir, halfWay);
	float exp = pow(base, 5);
	float fresnel = exp+fZero*(1.0-exp);
	*/

	float fresnel = 1 - clamp(abs(dot(worldNormal, normalize(eyeDir))), 0, 1);
	float diffuse = clamp(abs(dot(lightDir, worldNormal)), 0, 1);
	//gl_FragColor = pow(fresnel, 1.5) * fresnelColor + ambientColor + diffuse * diffuseColor;
	gl_FragColor.rgb = pow(fresnel, fresnelPow) * fresnelCol + ambientCol + diffuse * diffuseCol;
	gl_FragColor.a = 1.0;
}