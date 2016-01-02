#version 430

uniform vec4 uColor;
in flat int _layer;

void main()
{
	vec4 pos = gl_FragCoord;
	pos.z = _layer;
	
	if(pos.y > 16)
		gl_FragColor.g = 1.0f;
	else
		gl_FragColor.g = 0.0f;
	//gl_FragColor = uColor;
	gl_FragColor.r = _layer * 0.1;
	//gl_FragColor.g = 0.6;
	gl_FragColor.b = 0.6;
	gl_FragColor.a = 0.6;
}