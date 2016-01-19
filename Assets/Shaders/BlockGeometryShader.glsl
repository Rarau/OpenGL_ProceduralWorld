#version 150
 
layout(points) in;
layout (triangle_strip, max_vertices=3) out;

uniform uint case_to_numpolys[256];

void main()
{
	// emit one triangle per point
	gl_Position = gl_in[0].gl_Position;
    EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.03, 0.0, 0.0);
    EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.03, 0.0, 0.0, 0.0);
    EmitVertex();  
	
	EndPrimitive();
}