namespace engine
{
	class VertexBuffer
	{

	private:

		GLuint _vertexBufferID;
		GLenum _mode;
		// amount of vertices per mesh
		GLsizei _count;
		// size of the attributes
		GLsizei _stride;

	public:

		GLuint getVertexBufferID()
		{
			return _vertexBufferID;
		}

		VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride) :
		_mode(mode), _count(count), _stride(stride)
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

		void ConfigureVertexAttributes(GLint vertexPosition)
		{
			if (vertexPosition != -1)
			{
				// set vertices attributes
				glEnableVertexAttribArray(vertexPosition);
				// describe those attributes
				glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, _stride, NULL);
			}
		}

		void RenderVertexBuffer()
		{
			glDrawArrays(_mode, 0, _count);
		}		
	};
}