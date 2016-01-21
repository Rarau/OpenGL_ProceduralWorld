#version 430
 
layout(points) in;
layout (triangle_strip, max_vertices=3) out;

out vec4 vColor;

// texture array with density function values
layout(location = 3) uniform sampler2DArray uTextureArray;

// numpolys case table
uniform uint case_to_numpolys[256];



// Edge connection lookup table
//layout(location = 5) uniform int edge_connect_list[3840];
layout (std430) buffer edge_table
{ 
  int table[3840];  
};

// local vertex coordinates
// even if its only one float, the geometry shader receives an array
in vec3 localPosition[];

in mat4 MVP[];


void main()
{
	
	float separation = 1.0/32.0;
	
	// compute case:
	
	// check sign of each voxel vertex	
	
	// CAREFUL: x[0-1], y[0-1], z[0-31]
	vec3 scaledLocalPosition = vec3(localPosition[0].x + 1.0/64.0, localPosition[0].y + 1.0/64.0, localPosition[0].z * 32); // to match the 3d texture size (33x33x33)
	
	vec4 vertex0Value = texture(uTextureArray, vec3(scaledLocalPosition.x, scaledLocalPosition.y, scaledLocalPosition.z));	
	int v0 = 0;
	if(vertex0Value.r > 0.0){v0 = 1;};
	
	vec4 vertex1Value = texture(uTextureArray, vec3(scaledLocalPosition.x, scaledLocalPosition.y + separation, scaledLocalPosition.z));
	int v1 = 0;
	if(vertex1Value.r > 0.0){v1 = 2;};
	
	vec4 vertex2Value = texture(uTextureArray, vec3(scaledLocalPosition.x + separation, scaledLocalPosition.y + separation, scaledLocalPosition.z));
	int v2 = 0;
	if(vertex2Value.r > 0.0){v2 = 4;};
	
	vec4 vertex3Value = texture(uTextureArray, vec3(scaledLocalPosition.x + separation, scaledLocalPosition.y, scaledLocalPosition.z));
	int v3 = 0;
	if(vertex3Value.r > 0.0){v3 = 8;};
	
	
	vec4 vertex4Value = texture(uTextureArray, vec3(scaledLocalPosition.x, scaledLocalPosition.y, scaledLocalPosition.z + separation));	
	int v4 = 0;
	if(vertex4Value.r > 0.0){v4 = 16;};
	
	vec4 vertex5Value = texture(uTextureArray, vec3(scaledLocalPosition.x, scaledLocalPosition.y + separation, scaledLocalPosition.z + 1));
	int v5 = 0;
	if(vertex5Value.r > 0.0){v5 = 32;};
	
	vec4 vertex6Value = texture(uTextureArray, vec3(scaledLocalPosition.x + separation, scaledLocalPosition.y + (separation), scaledLocalPosition.z + 1));
	int v6 = 0;
	if(vertex6Value.r > 0.0){v6 = 64;};
	
	vec4 vertex7Value = texture(uTextureArray, vec3(scaledLocalPosition.x + separation, scaledLocalPosition.y, scaledLocalPosition.z + 1));
	int v7 = 0;
	if(vertex7Value.r > 0.0){v7 = 128;};
	
	// concatenate bits
	int voxelCase = v7|v6|v5|v4|v3|v2|v1|v0;
	int voxelcase2 = v7|v6|v5|v4|v3|v2|v1|v0;
	
	// look up table to see number of polys needed
	uint numpolys = case_to_numpolys[voxelCase];
	
	// which edges hold our vertices	
	vec3 triangles[5]; // careful, each component is the identifier of an edge
	triangles[0] = vec3( table[voxelcase2*5*3], table[voxelcase2*5*3 +1], table[voxelcase2*5*3 +2]);
	triangles[1] = vec3( table[voxelcase2*5*3 + 3], table[voxelcase2*5*3 + 3 + 1], table[voxelcase2*5*3 + 3 + 2]);
	triangles[2] = vec3( table[voxelcase2*5*3 + 6], table[voxelcase2*5*3 + 6 + 1], table[voxelcase2*5*3 + 6 + 2]);
	triangles[3] = vec3( table[voxelcase2*5*3 + 9], table[voxelcase2*5*3 + 9 + 1], table[voxelcase2*5*3 + 9 + 2]);
	triangles[4] = vec3( table[voxelcase2*5*3 + 12], table[voxelcase2*5*3 + 12 + 1], table[voxelcase2*5*3 + 12 + 2]);
	
	// debug the case
	// vec4 face_color = vec4(float(voxelCase)/255, float(numpolys * 45), 0.0, 1.0);
	vec4 face_color = vec4(float(numpolys)/10, 0.0, 0.0, 1.0);	
	
	//if(scaledLocalPosition.y + 1.0/32.0 >= 0.97f)
	//if(true)
	//if(table[62] == 10)
	//if(voxelCase != 0 && voxelCase != 255)
	if(numpolys != 0)
	{	
		// for(uint j = 0; j < numpolys; j++)
		// {
			vColor = face_color;
			
			// emit one triangle per point
			gl_Position = gl_in[0].gl_Position;
			EmitVertex();
			gl_Position = gl_in[0].gl_Position + MVP[0]*vec4(0.0, 1.0/32.0, 0.0, 0.0);
			EmitVertex();
			gl_Position = gl_in[0].gl_Position + MVP[0]*vec4(1.0/32.0, 0.0, 0.0, 0.0);
			EmitVertex();  
			
			EndPrimitive();
		// }
	}
	
}