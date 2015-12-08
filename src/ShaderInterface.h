namespace engine
{
	class  ShaderInterface
	{	

	private:

		ShaderLoader *shader;

		GLint _aPositionVertex;
		GLint _uColor;

		char *_vertexShaderString;
		char *_fragmentShaderString;
		char *_geometryShaderString;

		char* LoadTextFromFile(const char *file)
		{
			FILE *currentFile;
			errno_t errorCode = fopen_s(&currentFile, file, "rt");			 
			// point to the end of the file
			fseek(currentFile, 0, SEEK_END);
			// amount of characters in the file
			int count = (int)ftell(currentFile); 
			// go back to the beggining
			rewind(currentFile);
			// allocate space for all the characters
			char *data = (char*)malloc(sizeof(char) * (count + 1));
			// copy in the data space the characters of the file
			count = (int)fread(data, sizeof(char), count, currentFile);

			// add the string end character
			data[count] = '\0';

			// close the file
			fclose(currentFile);

			return data;
		}

	public:

		GLuint GetProgramHandle()
		{
			shader->GetProgramHandle();
		}

		GLint Get_aPositionVertex()
		{
			return _aPositionVertex;
		}

		GLint get_uColor()
		{
			return _uColor;
		}

		ShaderInterface(const char *VS, const char *FS)
		{
			// read shaders from strings
			_vertexShaderString = LoadTextFromFile(VS);
			_fragmentShaderString = LoadTextFromFile(FS);
			shader = new ShaderLoader(_vertexShaderString, _fragmentShaderString);
			// deallocate strings, we wont use them again
			free(_vertexShaderString);
			free(_fragmentShaderString);

			_aPositionVertex = glGetAttribLocation(shader->GetProgramHandle(), "aPositionVertex");
			_uColor = glGetUniformLocation(shader->GetProgramHandle(), "uColor");
		}

		ShaderInterface(const char *VS, const char *FS, const char *GS)
		{
			// read shaders from strings
			_vertexShaderString = LoadTextFromFile(VS);
			_fragmentShaderString = LoadTextFromFile(FS);
			_geometryShaderString = LoadTextFromFile(GS);

			shader = new ShaderLoader(_vertexShaderString, _fragmentShaderString, _geometryShaderString);
			// deallocate strings, we wont use them again
			free(_vertexShaderString);
			free(_fragmentShaderString);
			free(_geometryShaderString);

			_aPositionVertex = glGetAttribLocation(shader->GetProgramHandle(), "aPositionVertex");
			_uColor = glGetUniformLocation(shader->GetProgramHandle(), "uColor");
		}

		~ShaderInterface()
		{
			delete shader;
		}


	};	
}