attribute vec3 aPositionVertex;
attribute vec3 aPositionNormal;

uniform vec4 uColor;
uniform vec3 uLightPosition;
uniform float uInstanceSeparation;

uniform mat4 uModelToWorld;
uniform mat4 uModelToProjection;


// outputs
varying vec4 vFinalVertexColor;
out VS_OUT {
	int instanceID; 
	vec4 globalPos;
} vs_out;

void main()
{
	vec3 normal = normalize(gl_NormalMatrix * aPositionNormal);

	vec3 lightPosition = uLightPosition;

	float dotProduct = max(dot(normal, lightPosition), 0.0);

	vFinalVertexColor = dotProduct * uColor;

	vec3 instancePos = aPositionVertex + vec3(0.0, 0.0, uInstanceSeparation) * gl_InstanceID;
	
	vs_out.instanceID = gl_InstanceID;
	
	vs_out.globalPos = vec4(instancePos, 1.0);
	gl_Position = gl_ModelViewMatrix * vec4(instancePos, 1.0);
}