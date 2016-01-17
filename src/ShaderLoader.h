// GL ERROR CHECK
#define CHECK_GL_ERROR() CheckGLError(__FILE__, __LINE__)
// GL ERROR CHECK
namespace engine
{
	int CheckGLError(char *file, int line)
	{
		//return 0;
		GLenum glErr, glErr2;
		int retCode = 0;

		glErr = glErr2 = glGetError();
		while (glErr != GL_NO_ERROR)
		{
			char* str1 = (char*)gluErrorString(glErr);
			if (str1)
				printf("GL Error #%d(%s) in File %s at line: %d\n", glErr, str1, file, line);
				//cout << "GL Error #" << glErr << "(" << str1 << ") " << " in File " << file << " at line: " << line << endl;
			else
				printf("GL Error #%d in File %s at line: %d\n", glErr, file, line);
				//cout << "GL Error #" << glErr << " in File " << file << " at line: " << line << endl;
			retCode = 1;
			glErr = glGetError();
		}
		if (glErr2 != GL_NO_ERROR) while (1)Sleep(100);;

		return 0;
	}

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
			CHECK_GL_ERROR();

			glCompileShader(shaderHandle);
			CHECK_GL_ERROR();

			GLint compileSuccess = 0;
			GLchar compilerSpew[256];

			glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
			CHECK_GL_ERROR();
			if (!compileSuccess)
			{
				glGetShaderInfoLog(shaderHandle, sizeof(compilerSpew), 0, compilerSpew);
				printf("Shader \n%s\ncompileSuccess=%d\n", compilerSpew, compileSuccess);
				CHECK_GL_ERROR();
				while (1);;
			}

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
			CHECK_GL_ERROR();
			GLint linkSuccess;
			GLchar compilerSpew[256];
			glGetProgramiv(_programHandle, GL_LINK_STATUS, &linkSuccess);
			if (!linkSuccess)
			{
				glGetProgramInfoLog(_programHandle, sizeof(compilerSpew), 0, compilerSpew);
				printf("Shader Linker:\n%s\nlinkSuccess=%d\n", compilerSpew, linkSuccess);
				CHECK_GL_ERROR();
				while (1);;
			}
			printf("linked successful\n");
			CHECK_GL_ERROR();

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