uniform sampler2D texture0;

///////////////////////////////////////////////////////////////////////////////
//	Greyscale Fragment Shader
///////////////////////////////////////////////////////////////////////////////

vec4 get_greyscale_of(in vec4 color);
float get_luminosity(in vec3 color);


void main()
{
	gl_FragColor = get_greyscale_of(texture2D(texture0,gl_TexCoord[0].st));
}

float get_luminosity(in vec3 color)
{
	return dot(color, vec3(0.299, 0.587, 0.114));
}

vec4 get_greyscale_of(in vec4 color)
{
	float luminosity = get_luminosity(color.rgb);
	return vec4(luminosity, luminosity, luminosity, color.a);
}