#version 430

layout(triangles) in;
layout (triangle_strip, max_vertices=3) out;

in VS_OUT {
	int instanceID;
	vec4 globalPos;
} gs_in[];

out flat int _layer;

void main()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Layer = gs_in[i].instanceID;
		gl_Position = gl_in[i].gl_Position;
		_layer = gs_in[i].instanceID;
		EmitVertex();
	}
	
	EndPrimitive();

}