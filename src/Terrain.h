namespace engine
{
	class Terrain
	{

	public:
		static void FillDensityVolume(float x, float y, float z, float cubeSize)
		{
			// Generate 2 triangles at x,y,z (bottom left corner closer to the screen) with cubeSize
			float  vertices[] = {
				x, y, z,
				x, y + cubeSize, z,
				x + cubeSize, y + cubeSize, z,
				x + cubeSize, y, z
			};

			int indices[] = {
				0, 1, 3,
				1, 2, 3
			};

			GLuint VB, IBO;


			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

			//glCullFace(GL_BACK);
			//ts = get_tileset(tilesets, tile_gid);
			// attribute_pos (=0) is position of each corner
			// each corner has 3 floats (x, y, z)
			// there is no gap between the 3 floats and hence the stride is 3*sizeof(float)
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)vertices);
			glEnableVertexAttribArray(0);


			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			//glDrawArrays(GL_TRIANGLE_FAN, 0, 60);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			// Render 33 instances of them
			// Using the pixel shader to render to 3D texture
		}

	};
}