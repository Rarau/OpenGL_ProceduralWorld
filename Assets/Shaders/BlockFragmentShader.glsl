#version 430 core
uniform vec4 uColor;

//in vec4 vColor;
in fData
{
    vec3 normal;
    vec4 vColor;
};

void main()
{
	vec4 ambient = vec4(0.15, 0.49, 0.05, 1.0);
	vec4 col = vec4(0.93, 0.96, 0.64, 1.0);
	vec3 lightDir = vec3(0.5, 0.5, 0.5);
	normalize(lightDir);
	// if(gl_FragColor.r < 0)
	// {
		// gl_FragColor.r = 0;
	// }
	// else
	
	
	gl_FragColor = mix (ambient, col, dot(lightDir, normalize(normal)));
	/*
	gl_FragColor.g = 0.1;
	gl_FragColor.b = 0.1;
	gl_FragColor.a = 0.1;
	*/
}