#version 430
 
layout(points) in;
layout (triangle_strip, max_vertices=3) out;

layout(location = 3) uniform sampler2DArray uTextureArray;
uniform uint case_to_numpolys[256];


void main()
{
	// compute case
	// 1 - check sign of each voxel vertex
	vec4 vertex1Value = texture(uTextureArray, vec3(1f, 1f, 1f));
	
	// value arrives here /2 WTF??
	if(vertex1Value.r == 5.0f)
	{	
		//PROBLEM!!! We need the ModelViewProjectionMatrix to project points!

		// emit one triangle per point
		gl_Position = gl_in[0].gl_Position;
		EmitVertex();
		gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.03, 0.0, 0.0);
		EmitVertex();
		gl_Position = gl_in[0].gl_Position + vec4(0.03, 0.0, 0.0, 0.0);
		EmitVertex();  
		
		EndPrimitive();
	}
	
}