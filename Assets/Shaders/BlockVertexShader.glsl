attribute vec3 aPositionVertex;
uniform mat4 uModelToProjection;

out vec3 localPosition;

void main()
{
	gl_Position = uModelToProjection * vec4(aPositionVertex, 1.0);	
	localPosition = aPositionVertex;	
}