#version 430

uniform vec4 uColor;
in flat int _layer;

in GS_OUT {
    vec4 wCoords;    
} ps_in;

//in vec4 worldCoords;
 
void main()
{

	vec4 pos = ps_in.wCoords;

	//vec4 localPos;
	//pos.z = _layer;	
	
	// we are rendering to a texture buffer with 1 float per pixel
	
	 if(pos.z > 0.5)
	 {
		 
		float sphereSurface = (pos.x - 0.0)*(pos.x - 0.0)+ (pos.y - 0.0)*(pos.y - 0.0) + (pos.z - 0.0)*(pos.z - 0.0);
		if(sphereSurface < 0.5)
		{
			gl_FragColor.r = 0.8f;	
		}
		else
		{
			gl_FragColor.r = -0.8f;
		}	
		
		
	 }
	
	
	
	
	// if(ps_in.wCoords.y > 0.5)
	// {		
		// gl_FragColor.r = 10.0f;	
	// }
	// else
	// {
		// gl_FragColor.r = -10.0f;
	// }	
	
	
	// if(pos.z < 1f)
	// {
		// gl_FragColor.r = 10.0f;	
	// }
	// else
	// {
		// gl_FragColor.r = -10.0f;
	// }		
	
}