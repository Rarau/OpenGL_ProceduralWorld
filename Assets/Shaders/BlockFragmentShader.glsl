#version 430 core
uniform vec4 uColor;

in vec4 vColor;

void main()
{
	// if(gl_FragColor.r < 0)
	// {
		// gl_FragColor.r = 0;
	// }
	// else
	{
		gl_FragColor = vColor;
		gl_FragColor.r *= 1.50;
	}
	/*
	gl_FragColor.g = 0.1;
	gl_FragColor.b = 0.1;
	gl_FragColor.a = 0.1;
	*/
}