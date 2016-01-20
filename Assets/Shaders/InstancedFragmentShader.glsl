#version 430

uniform vec4 uColor;
in flat int _layer;

void main()
{
	vec4 pos = gl_FragCoord;
	pos.z = _layer;
	
	//TO-DO: Evaluate the density function here
	
	// we are rendering to a texture buffer with 1 float per pixel
	if(pos.y < 15f)
	{
		gl_FragColor.r = 10.0f;	
	}
	else
	{
		gl_FragColor.r = -10.0f;
	}	
	
}