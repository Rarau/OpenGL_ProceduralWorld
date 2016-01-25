#version 430

layout(triangles) in;
layout (triangle_strip, max_vertices=3) out;

in VS_OUT {
	int instanceID;	
	vec4 worldCoord;
} gs_in[];

out gl_PerVertex {
    vec4 wCoords;    
} gs_out;

out flat int _layer;

void main()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Layer = gs_in[i].instanceID;
		gl_Position = gl_in[i].gl_Position;
		_layer = gs_in[i].instanceID;	
		gs_out.wCoords = gs_in[i].worldCoord;		
		EmitVertex();
	}
	
	EndPrimitive();

}