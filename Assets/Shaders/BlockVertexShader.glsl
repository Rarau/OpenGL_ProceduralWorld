attribute vec3 aPositionVertex;

uniform mat4 _ModelToWorld;
out vec3 localPosition;
out mat4 MVP;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * vec4(aPositionVertex, 1.0);
	
	MVP = gl_ModelViewProjectionMatrix;
	localPosition = aPositionVertex;	
	
	
}