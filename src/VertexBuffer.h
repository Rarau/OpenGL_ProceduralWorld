namespace engine
{
	class VertexBuffer
	{

	private:

		GLuint _vertexBufferID;

	public:

		GLuint getVertexBufferID()
		{
			return _vertexBufferID;
		}

		VertexBuffer(const GLvoid *data, GLsizeiptr size)
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
	};
}