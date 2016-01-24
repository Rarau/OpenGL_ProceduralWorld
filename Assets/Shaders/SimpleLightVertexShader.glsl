attribute vec3 aPositionVertex;
attribute vec3 aPositionNormal;

uniform vec4 uColor;
uniform vec3 uLightPosition;

uniform mat4 uModelToProjection;

varying vec4 vFinalVertexColor;

void main()
{
	vec3 normal = normalize(gl_NormalMatrix * aPositionNormal);

	vec3 lightPosition = uLightPosition;

	float dotProduct = max(dot(normal, lightPosition), 0.0);

	vFinalVertexColor = dotProduct * uColor;

	gl_Position = uModelToProjection * vec4(aPositionVertex, 1.0);
}