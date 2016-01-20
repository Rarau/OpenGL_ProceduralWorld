#version 430
 
layout(points) in;
layout (triangle_strip, max_vertices=3) out;

// texture array with density function values
layout(location = 3) uniform sampler2DArray uTextureArray;

// numpolys case table
uniform uint case_to_numpolys[256];

// local vertex coordinates
// even if its only one float, the geometry shader receives an array
in vec3 localPosition[];


void main()
{
	// compute case
	// 1 - check sign of each voxel vertex
	
	vec4 vertex1Value = texture(uTextureArray, vec3(1f, 1f, 1f));
	
	
	// if(vertex1Value.r == 10.0f)	
	if(localPosition[0].y < 0.3f)
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