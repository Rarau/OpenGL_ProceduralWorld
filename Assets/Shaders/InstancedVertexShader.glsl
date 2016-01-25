#version 430

attribute vec3 aPositionVertex;
attribute vec3 aPositionNormal;

uniform float uInstanceSeparation;

layout(location = 3) uniform mat4 uModelToWorld;
layout(location = 4) uniform mat4 uModelToProjection;


// outputs
varying vec4 vFinalVertexColor;
out VS_OUT {
	int instanceID; 
	vec4 globalPos;
} vs_out;

void main()
{
	vec3 instancePos = aPositionVertex + vec3(0.0, 0.0, uInstanceSeparation) * gl_InstanceID;
	
	vs_out.instanceID = gl_InstanceID;
	
	vs_out.globalPos =  uModelToWorld * vec4(instancePos, 1.0);	
	gl_Position = uModelToProjection * vec4(instancePos, 1.0);
}