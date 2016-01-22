#version 430

uniform vec4 uColor;
in flat int _layer;

void main()
{
	vec4 pos = gl_FragCoord;
	
	pos.z = _layer;
	
	//TO-DO: Evaluate the density function here
	
	// we are rendering to a texture buffer with 1 float per pixel
	
	 
	float sphereSurface = (pos.x - 18.0)*(pos.x - 18.0)+ (pos.y - 18.0)*(pos.y - 18.0) + (pos.z - 18.0)*(pos.z - 18.0);
	if(sphereSurface < 260f)
	{
		gl_FragColor.r = 10.0f;	
	}
	else
	{
		gl_FragColor.r = -10.0f;
	}	
	
	// if(pos.z < 15f)
	// {
		// gl_FragColor.r = 10.0f;	
	// }
	// else
	// {
		// gl_FragColor.r = -10.0f;
	// }	
	
}