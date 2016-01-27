#version 430
 
layout(points) in;

layout (triangle_strip, max_vertices=15) out;
//out vec4 vColor;
//out vec4 faceNormal;
out fData
{
    vec3 normal;
    vec4 vColor;
	vec4 pos;
}frag;   

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

uniform mat4 uModelToProjection;


// density values at the corners of the voxel
float vertexValues[8];

// voxel corners view positions
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
	
	float value1 = vertexValues[point1];
	float value2 = vertexValues[point2];
	
	float modvalue1 = abs(value1);
	float modvalue2 = abs(value2);
	
	float sumInv = 1/(modvalue1 + modvalue2);
	float w1 = modvalue1 * sumInv;
	float w2 = modvalue2 * sumInv;
	
	//position = pPos[point2];
	position = pPos[point1] * w2 + pPos[point2] * w1;	
	//position = vec4((pPos[point1].x + pPos[point2].x)*0.5, (pPos[point1].y + pPos[point2].y)*0.5, (pPos[point1].z + pPos[point2].z)*0.5, 1.0);
}

uniform ivec2 edge_to_point_table[12] = {
	ivec2(0, 1),
	ivec2(1, 2),
	ivec2(2, 3),
	ivec2(3, 0),
	ivec2(4, 5),
	ivec2(5, 6),
	ivec2(6, 7),
	ivec2(7, 4),
	ivec2(4, 0),
	ivec2(1, 5),
	ivec2(2, 6),
	ivec2(3, 7)
};

void edge_to_point(in uint edge, out vec4 position)
{	
	position = vec4(0.0, 0.0, 0.0, 0.0);
	ivec2 p = edge_to_point_table[edge];
	corners_to_point(p.x, p.y, position);
	/*
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
		corners_to_point(7,4, position);
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
	}*/
}


void main()
{
	// Calculate positions of the 8 corners of the voxel:
	// pPos[0] = gl_in[0].gl_Position;
	// pPos[1] = gl_in[0].gl_Position + uModelToProjection*vec4(0.0, 1.0/32.0, 0.0, 0.0);
	// pPos[2] = gl_in[0].gl_Position + uModelToProjection*vec4(1.0/32.0, 1.0/32.0, 0.0, 0.0);
	// pPos[3] = gl_in[0].gl_Position + uModelToProjection*vec4(1.0/32.0, 0.0, 0.0, 0.0);
	
	// pPos[4] = gl_in[0].gl_Position + uModelToProjection*vec4(0.0, 0.0, 1.0/32.0, 0.0);
	// pPos[5] = gl_in[0].gl_Position + uModelToProjection*vec4(0.0, 1.0/32.0, 1.0/32.0, 0.0);
	// pPos[6] = gl_in[0].gl_Position + uModelToProjection*vec4(1.0/32.0, 1.0/32.0, 1.0/32.0, 0.0);
	// pPos[7] = gl_in[0].gl_Position + uModelToProjection*vec4(1.0/32.0, 0.0, 1.0/32.0, 0.0);
	
	// Calculate positions of the 8 corners of the voxel:
	float separation = 1.0/32.0;
	vec4 local = vec4(localPosition[0].x, localPosition[0].y, localPosition[0].z, 1.0);
	pPos[0] = local;
	pPos[1] = local + vec4(0.0, separation, 0.0, 0.0);
	pPos[2] = local + vec4(separation, separation, 0.0, 0.0);
	pPos[3] = local + vec4(separation, 0.0, 0.0, 0.0);
	
	pPos[4] = local + vec4(0.0, 0.0, separation, 0.0);
	pPos[5] = local + vec4(0.0, separation, separation, 0.0);
	pPos[6] = local + vec4(separation, separation, separation, 0.0);
	pPos[7] = local + vec4(separation, 0.0, separation, 0.0);
	
	
	// compute case: ---------------------------------------------------------------------------------------------------	
	// check sign of each voxel vertex	
	
	// CAREFUL: x[0-1], y[0-1], z[0-31]
	vec3 scaledLocalPosition = vec3(localPosition[0].x + 1.0/66.0, localPosition[0].y + 1.0/66.0, localPosition[0].z * 32); // to match the 3d texture size (33x33x33)
	
	vec4 vertex0Value = texture(uTextureArray, vec3(scaledLocalPosition.x, scaledLocalPosition.y, scaledLocalPosition.z));	
	int v0 = 0;
	vertexValues[0] = vertex0Value.r;
	if(vertexValues[0] > 0.0){v0 = 1;};
	
	vec4 vertex1Value = texture(uTextureArray, vec3(scaledLocalPosition.x, scaledLocalPosition.y + separation, scaledLocalPosition.z));
	int v1 = 0;
	vertexValues[1] = vertex1Value.r;
	if(vertexValues[1] > 0.0){v1 = 2;};
	
	vec4 vertex2Value = texture(uTextureArray, vec3(scaledLocalPosition.x + separation, scaledLocalPosition.y + separation, scaledLocalPosition.z));
	int v2 = 0;
	vertexValues[2] = vertex2Value.r;
	if(vertexValues[2] > 0.0){v2 = 4;};
	
	vec4 vertex3Value = texture(uTextureArray, vec3(scaledLocalPosition.x + separation, scaledLocalPosition.y, scaledLocalPosition.z));
	int v3 = 0;
	vertexValues[3] = vertex3Value.r;
	if(vertexValues[3] > 0.0){v3 = 8;};
	
	
	vec4 vertex4Value = texture(uTextureArray, vec3(scaledLocalPosition.x, scaledLocalPosition.y, scaledLocalPosition.z + 1));	
	int v4 = 0;
	vertexValues[4] = vertex4Value.r;
	if(vertexValues[4] > 0.0){v4 = 16;};
	
	vec4 vertex5Value = texture(uTextureArray, vec3(scaledLocalPosition.x, scaledLocalPosition.y + separation, scaledLocalPosition.z + 1));
	int v5 = 0;
	vertexValues[5] = vertex5Value.r;
	if(vertexValues[5] > 0.0){v5 = 32;};
	
	vec4 vertex6Value = texture(uTextureArray, vec3(scaledLocalPosition.x + separation, scaledLocalPosition.y + (separation), scaledLocalPosition.z + 1));
	int v6 = 0;
	vertexValues[6] = vertex6Value.r;
	if(vertexValues[6] > 0.0){v6 = 64;};
	
	vec4 vertex7Value = texture(uTextureArray, vec3(scaledLocalPosition.x + separation, scaledLocalPosition.y, scaledLocalPosition.z + 1));
	int v7 = 0;
	vertexValues[7] = vertex7Value.r;
	if(vertexValues[7] > 0.0){v7 = 128;};
	
	// concatenate bits
	//int voxelCase = v7|v6|v5|v4|v3|v2|v1|v0; // seems correct
	//int voxelcase2 = v7|v6|v5|v4|v3|v2|v1|v0;
	int voxelCase = v7+v6+v5+v4+v3+v2+v1+v0; // seems correct	
	int voxelcase2 = v7+v6+v5+v4+v3+v2+v1+v0;
	//int voxelCase = 15;
	//int voxelcase2 = 15;
	
	// End compute case: -----------------------------------------------------------------------------------------------
	
	// look up table to see number of polys needed
	uint numpolys = case_to_numpolys[voxelCase]; // Correct
	
	// which edges hold our vertices	
	uvec3 rawTriangles[5]; // careful, each component is the identifier of an edge
	rawTriangles[0] = uvec3( table[voxelcase2*5*3], table[voxelcase2*5*3 +1], table[voxelcase2*5*3 +2]);
	rawTriangles[1] = uvec3( table[voxelcase2*5*3 + 3], table[voxelcase2*5*3 + 3 + 1], table[voxelcase2*5*3 + 3 + 2]);
	rawTriangles[2] = uvec3( table[voxelcase2*5*3 + 6], table[voxelcase2*5*3 + 6 + 1], table[voxelcase2*5*3 + 6 + 2]);
	rawTriangles[3] = uvec3( table[voxelcase2*5*3 + 9], table[voxelcase2*5*3 + 9 + 1], table[voxelcase2*5*3 + 9 + 2]);
	rawTriangles[4] = uvec3( table[voxelcase2*5*3 + 12], table[voxelcase2*5*3 + 12 + 1], table[voxelcase2*5*3 + 12 + 2]);
	
	//vec4 triPos;
	//edge_to_point(0, triPos);
	
	// final triangles. Already in view space
	vec4 finalTriangle1[3]; // first triangle
	edge_to_point(rawTriangles[0].x, finalTriangle1[0]);
	edge_to_point(rawTriangles[0].y, finalTriangle1[1]);
	edge_to_point(rawTriangles[0].z, finalTriangle1[2]);	
	
	vec4 finalTriangle2[3]; // second triangle
	edge_to_point(rawTriangles[1].x, finalTriangle2[0]);
	edge_to_point(rawTriangles[1].y, finalTriangle2[1]);
	edge_to_point(rawTriangles[1].z, finalTriangle2[2]);	
	
	vec4 finalTriangle3[3]; // third triangle
	edge_to_point(rawTriangles[2].x, finalTriangle3[0]);
	edge_to_point(rawTriangles[2].y, finalTriangle3[1]);
	edge_to_point(rawTriangles[2].z, finalTriangle3[2]);
	
	vec4 finalTriangle4[3]; // fourth triangle
	edge_to_point(rawTriangles[3].x, finalTriangle4[0]);
	edge_to_point(rawTriangles[3].y, finalTriangle4[1]);
	edge_to_point(rawTriangles[3].z, finalTriangle4[2]);
	
	vec4 finalTriangle5[3]; // fifth triangle
	edge_to_point(rawTriangles[4].x, finalTriangle5[0]);
	edge_to_point(rawTriangles[4].y, finalTriangle5[1]);
	edge_to_point(rawTriangles[4].z, finalTriangle5[2]);
	
	
	
	// debug numpolys
	float col = 0.5;
	vec4 face_color = vec4(col, col, col, 1.0);
	//vec4 face_color = vec4(float(numpolys)/10, 0.0, 0.0, 1.0);
	
	//vec4 face_color = vec4(finalTriangle3[0].x, 0.0, 0.0, 1.0);
	
	//if(scaledLocalPosition.y + 1.0/32.0 >= 0.97f)
	//if(true)
	//if(table[62] == 10)
	//if(voxelCase != 0 && voxelCase != 255)
	if(numpolys > 0)
	{	
		frag.vColor = face_color;
		// for(uint j = 0; j < numpolys; j++)
		// {
			// vColor = face_color;		
			
			//emit one triangle per point
			//Test triangles. To-do: create the real triangles.
			// gl_Position = gl_in[0].gl_Position + uModelToProjection*vec4(0.0, float(j), 0.0, 0.0);
			// EmitVertex();
			// gl_Position = gl_in[0].gl_Position + uModelToProjection*vec4(0.0, 1.0/32.0 + float(j), 0.0, 0.0);
			// EmitVertex();
			// gl_Position = gl_in[0].gl_Position + uModelToProjection*vec4(1.0/32.0, 0.0 + float(j), 0.0, 0.0);
			// EmitVertex();  
			
			// EndPrimitive();
		// }		
				
		
		// emit first triangle
		// Test triangles. To-do: create the real triangles.
		vec3 faceNormal = -cross((finalTriangle1[0].xyz - finalTriangle1[1].xyz), (finalTriangle1[0].xyz - finalTriangle1[2].xyz));
		normalize(faceNormal);
		//faceNormal = vec3(1);
		gl_Position = uModelToProjection*finalTriangle1[0];
		frag.normal = faceNormal;
		frag.pos = finalTriangle1[0];
		EmitVertex();
		gl_Position = uModelToProjection*finalTriangle1[1];
		frag.normal = faceNormal;
		frag.pos = finalTriangle1[0];
		EmitVertex();
		gl_Position = uModelToProjection*finalTriangle1[2];
		frag.normal = faceNormal;
		frag.pos = finalTriangle1[0];
		EmitVertex();  
		
		EndPrimitive();
		
		if(numpolys > 1)
		{
			// emit second triangle
			faceNormal = -cross((finalTriangle2[0].xyz - finalTriangle2[1].xyz), (finalTriangle2[0].xyz - finalTriangle2[2].xyz));
			normalize(faceNormal);

			gl_Position = uModelToProjection*finalTriangle2[0];
			frag.normal = faceNormal;
			frag.pos = finalTriangle2[0];
			EmitVertex();
			gl_Position = uModelToProjection*finalTriangle2[1];
			frag.normal = faceNormal;
			frag.pos = finalTriangle2[1];
			EmitVertex();
			gl_Position = uModelToProjection*finalTriangle2[2];
			frag.normal = faceNormal;
			frag.pos = finalTriangle2[2];
			EmitVertex();  
			
			EndPrimitive();
			
			if(numpolys > 2)
			{
				// emit third triangle
			faceNormal = -cross((finalTriangle3[0].xyz - finalTriangle3[1].xyz), (finalTriangle3[0].xyz - finalTriangle3[2].xyz));
			normalize(faceNormal);

			gl_Position = uModelToProjection*finalTriangle3[0];
			frag.normal = faceNormal;
			frag.pos = finalTriangle3[0];
			EmitVertex();
			gl_Position = uModelToProjection*finalTriangle3[1];
			frag.normal = faceNormal;
			frag.pos = finalTriangle3[1];
			EmitVertex();
			gl_Position = uModelToProjection*finalTriangle3[2];
			frag.normal = faceNormal;
			frag.pos = finalTriangle3[2];
			EmitVertex();   
				
				EndPrimitive();
				
				if(numpolys > 3)
				{
					// emit fourth triangle
					faceNormal = -cross((finalTriangle4[0].xyz - finalTriangle4[1].xyz), (finalTriangle4[0].xyz - finalTriangle4[2].xyz));
					normalize(faceNormal);

					gl_Position = uModelToProjection*finalTriangle4[0];
					frag.normal = faceNormal;
					frag.pos = finalTriangle4[0];
					EmitVertex();
					gl_Position = uModelToProjection*finalTriangle4[1];
					frag.normal = faceNormal;
					frag.pos = finalTriangle4[1];
					EmitVertex();
					gl_Position = uModelToProjection*finalTriangle4[2];
					frag.normal = faceNormal;
					frag.pos = finalTriangle4[2];
					EmitVertex();  
					
					EndPrimitive();
					
					if(numpolys > 4)
					{
						// emit fifth triangle
						faceNormal = -cross((finalTriangle5[0].xyz - finalTriangle5[1].xyz), (finalTriangle5[0].xyz - finalTriangle5[2].xyz));
						normalize(faceNormal);

						gl_Position = uModelToProjection*finalTriangle5[0];
						frag.normal = faceNormal;
						frag.pos = finalTriangle5[0];
						EmitVertex();
						gl_Position = uModelToProjection*finalTriangle5[1];
						frag.normal = faceNormal;
						frag.pos = finalTriangle5[1];
						EmitVertex();
						gl_Position = uModelToProjection*finalTriangle5[2];
						frag.normal = faceNormal;
						frag.pos = finalTriangle5[2];
						EmitVertex();  
						
						EndPrimitive();
					}
				}
			}
		}
	}
	
}