attribute vec3 aPositionVertex;

out vec3 localPosition;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * vec4(aPositionVertex, 1.0);
	localPosition = aPositionVertex;
	
}