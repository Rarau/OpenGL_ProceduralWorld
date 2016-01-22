#version 430
 
layout(points) in;
layout (triangle_strip, max_vertices=15) out;

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


// density values at the corners of the voxel
float v[8];

// voxel corners global positions
vec4 pPos[8];
// vec4 p1Pos;
// vec4 p2Pos;
// vec4 p3Pos;
// vec4 p4Pos;
// vec4 p5Pos;
// vec4 p6Pos;
// vec4 p7Pos;

void corners_to_point(in int point1, in int point2, out vec4 position)
{
	position = vec4(1.0, 1.0, 1.0, 0.0);
	
	// float w1 =
	// float w2 =
	
}

void edge_to_point(in int edge, out vec4 position)
{	
	position = vec4(0.0, 0.0, 0.0, 0.0);

	if(edge == 0)
	{
		corners_to_point(0,1, position);
	}
	if(edge == 1)
	{
		corners_to_point(1,2, position);
	}
	if(edge == 2)
	{
		corners_to_point(2,3, position);
	}	
	if(edge == 3)
	{		
		corners_to_point(3,0, position);
	}
	if(edge == 4)
	{
		corners_to_point(4,5, position);
	}
	if(edge == 5)
	{
		corners_to_point(5,6, position);
	}
	if(edge == 6)
	{
		corners_to_point(6,7, position);
	}
	if(edge == 7)
	{
		corners_to_point(7,8, position);
	}
	if(edge == 8)
	{
		corners_to_point(4,0, position);	
	}
	if(edge == 9)
	{
		corners_to_point(1,5, position);
	}	
	if(edge == 10)
	{		
		corners_to_point(2,6, position);
	}
	if(edge == 11)
	{
		corners_to_point(3,7, position);
	}
}


void main()
{
	//Calculate positions of the 8 corners of the voxel:
	pPos[0] = gl_in[0].gl_Position;
	pPos[1] = gl_in[0].gl_Position + MVP[0]*vec4(0.0, 1.0/32.0, 0.0, 0.0);
	pPos[2] = gl_in[0].gl_Position + MVP[0]*vec4(1.0/32.0, 1.0/32.0, 0.0, 0.0);
	pPos[3] = gl_in[0].gl_Position + MVP[0]*vec4(1.0/32.0, 0.0, 0.0, 0.0);
	
	pPos[4] = gl_in[0].gl_Position + MVP[0]*vec4(0.0, 0.0, 1.0/32.0, 0.0);
	pPos[5] = gl_in[0].gl_Position + MVP[0]*vec4(0.0, 1.0/32.0, 1.0/32.0, 0.0);
	pPos[6] = gl_in[0].gl_Position + MVP[0]*vec4(1.0/32.0, 1.0/32.0, 1.0/32.0, 0.0);
	pPos[7] = gl_in[0].gl_Position + MVP[0]*vec4(1.0/32.0, 0.0, 1.0/32.0, 0.0);
	
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
	vec3 rawTriangles[5]; // careful, each component is the identifier of an edge
	rawTriangles[0] = vec3( table[voxelcase2*5*3], table[voxelcase2*5*3 +1], table[voxelcase2*5*3 +2]);
	rawTriangles[1] = vec3( table[voxelcase2*5*3 + 3], table[voxelcase2*5*3 + 3 + 1], table[voxelcase2*5*3 + 3 + 2]);
	rawTriangles[2] = vec3( table[voxelcase2*5*3 + 6], table[voxelcase2*5*3 + 6 + 1], table[voxelcase2*5*3 + 6 + 2]);
	rawTriangles[3] = vec3( table[voxelcase2*5*3 + 9], table[voxelcase2*5*3 + 9 + 1], table[voxelcase2*5*3 + 9 + 2]);
	rawTriangles[4] = vec3( table[voxelcase2*5*3 + 12], table[voxelcase2*5*3 + 12 + 1], table[voxelcase2*5*3 + 12 + 2]);
	
	vec4 triPos;
	edge_to_point(0, triPos);
	
	
	// debug the case
	// vec4 face_color = vec4(float(voxelCase)/255, float(numpolys * 45), 0.0, 1.0);
	//vec4 face_color = vec4(float(numpolys)/10, 0.0, test(), 1.0);
	
	vec4 face_color = vec4(triPos.x, 0.0, 0.0, 1.0);
	
	//if(scaledLocalPosition.y + 1.0/32.0 >= 0.97f)
	//if(true)
	//if(table[62] == 10)
	//if(voxelCase != 0 && voxelCase != 255)
	if(numpolys != 0)
	{	
		for(uint j = 0; j < numpolys; j++)
		{
			vColor = face_color;
			
			
			// emit one triangle per point
			// Test triangles. To-do: create the real triangles.
			gl_Position = gl_in[0].gl_Position + MVP[0]*vec4(0.0, float(j), 0.0, 0.0);
			EmitVertex();
			gl_Position = gl_in[0].gl_Position + MVP[0]*vec4(0.0, 1.0/32.0 + float(j), 0.0, 0.0);
			EmitVertex();
			gl_Position = gl_in[0].gl_Position + MVP[0]*vec4(1.0/32.0, 0.0 + float(j), 0.0, 0.0);
			EmitVertex();  
			
			EndPrimitive();
		}
	}
	
}