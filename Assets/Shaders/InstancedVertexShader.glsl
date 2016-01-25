

attribute vec3 aPositionVertex;

uniform float uInstanceSeparation;

uniform mat4 uModelToWorld;
uniform mat4 uModelToProjection;


// outputs
out VS_OUT {
	int instanceID;
	vec4 worldCoord;	
} vs_out;

void main()
{
	vec3 instancePos = aPositionVertex + vec3(0.0, 0.0, uInstanceSeparation) * gl_InstanceID;
	
	vs_out.instanceID = gl_InstanceID;	
	vs_out.worldCoord = uModelToWorld * vec4(instancePos, 1.0);	
	gl_Position = gl_ModelViewMatrix * vec4(instancePos, 1.0);
}