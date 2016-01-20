attribute vec3 aPositionVertex;

out float test;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * vec4(aPositionVertex, 1.0);
	test = 1.0f;
	
}