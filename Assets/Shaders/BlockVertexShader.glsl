attribute vec3 aPositionVertex;
uniform int edge_connect_list[3840];

out vec3 localPosition;
out mat4 MVP;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * vec4(aPositionVertex, 1.0);
	
	MVP = gl_ModelViewProjectionMatrix;
	localPosition = aPositionVertex;	
	
	int i = edge_connect_list[0];
}