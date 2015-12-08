namespace engine
{
	class VertexBuffer
	{

	private:

		GLuint _vertexBufferID;
		ShaderInterface *_shader;

		GLenum _mode;
		// amount of vertices per mesh
		GLsizei _count;
		// size of the attributes
		GLsizei _stride;		

		// offset in the vertex array
		GLvoid *_positionOffset;
		GLvoid *_normalOffset;

	public:

		GLuint getVertexBufferID()
		{
			return _vertexBufferID;
		}

		VertexBuffer(const GLvoid *data, 
			GLsizeiptr size, 
			GLenum mode, 
			GLsizei count, 
			GLsizei stride,
			ShaderInterface *shader,
			GLvoid *positionOffset,
			GLvoid *normalOffset) :
			_mode(mode), _count(count), _stride(stride), _shader(shader), _positionOffset(positionOffset), _normalOffset(normalOffset)
		{
			glGenBuffers(1, &_vertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		~VertexBuffer()
		{
			glDeleteBuffers(1, &_vertexBufferID);
			_vertexBufferID = 0;
		}

		void ConfigureVertexAttributes()
		{
			if (_shader->Get_aPositionVertex() != -1)
			{
				// set vertices attributes
				glEnableVertexAttribArray(_shader->Get_aPositionVertex());
				// describe those attributes
				glVertexAttribPointer(_shader->Get_aPositionVertex(), 3, GL_FLOAT, GL_FALSE, _stride, _positionOffset);
			}

			if (_shader->Get_aNormalVertex() != -1)
			{
				glEnableVertexAttribArray(_shader->Get_aNormalVertex());
				glVertexAttribPointer(_shader->Get_aNormalVertex(), 3, GL_FLOAT, GL_FALSE, _stride, _normalOffset);
			}
		}

		void RenderVertexBuffer()
		{
			glDrawArrays(_mode, 0, _count);
		}		
	};
}