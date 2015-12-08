namespace engine
{
	class ShaderLoader
	{

	private:

		GLuint _programHandle;			

	public:

		GLuint GetProgramHandle()
		{
			return _programHandle;
		}

		GLuint CompileShader(GLenum shader, const char *source)
		{
			GLuint shaderHandle = glCreateShader(shader);
			glShaderSource(shaderHandle, 1, &source, NULL);
			glCompileShader(shaderHandle);

			return shaderHandle;
		}

		//VS: vertex shader, FS: fragment shader
		ShaderLoader(const char *sourceVS, const char *sourceFS)
		{
			_programHandle = glCreateProgram();

			GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, sourceVS);
			GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, sourceFS);

			glAttachShader(_programHandle, vertexShader);
			glAttachShader(_programHandle, fragmentShader);

			glLinkProgram(_programHandle);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

		}

		//VS: vertex shader, FS: fragment shader, GS: geometry shader
		ShaderLoader(const char *sourceVS, const char *sourceFS, const char *sourceGS)
		{
			_programHandle = glCreateProgram();

			GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, sourceVS);
			GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, sourceFS);
			GLuint geometryShader = CompileShader(GL_GEOMETRY_SHADER, sourceGS);

			glAttachShader(_programHandle, vertexShader);
			glAttachShader(_programHandle, fragmentShader);
			glAttachShader(_programHandle, geometryShader);

			glLinkProgram(_programHandle);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			glDeleteShader(geometryShader);
		}
		~ShaderLoader()
		{
			glDeleteProgram(_programHandle);
		}
		
	};
}