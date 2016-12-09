uniform sampler2D texture0;

///////////////////////////////////////////////////////////////////////////////
//	Coloured In Fragment Shader
///////////////////////////////////////////////////////////////////////////////
//
//	This shader blends the texture values with the gl_Color by 
//	desaturating the texture values and then colourising them.
//	The amount of desaturation is proportional to the saturation of
//	gl_Color, and the amount of colourisation is inversly proportional
//	to this, resulting in "Coloured in" objects rather than the dark
//	subtractive effect of changing vertex colours.
//
///////////////////////////////////////////////////////////////////////////////


vec3 get_greyscale_of(in vec3 color);
float get_luminosity(in vec3 color);
float get_saturation(in float ma, in float mi);
float get_saturation(in vec3 color);
void get_max_and_min(in vec3 color, out float ma, out float mi);
float get_max_min_diff(in vec3 color);

void main()
{
	vec4 textureColor = texture2D(texture0,gl_TexCoord[0].st);
	vec3 greyscaleTextureColor = get_greyscale_of(textureColor.rgb);
	float sat = get_saturation(gl_Color.rgb);

	vec4 blendedTextureColor;
	blendedTextureColor.rgb = sat*greyscaleTextureColor + (1.0f - sat)*textureColor.rgb;
	blendedTextureColor.a = textureColor.a;

	gl_FragColor = blendedTextureColor*gl_Color;
}




vec3 get_greyscale_of(in vec3 color)
{
	float luminosity = get_luminosity(color);
	return vec3(luminosity, luminosity, luminosity);
}

float get_luminosity(in vec3 color)
{
	return dot(color, vec3(0.299f, 0.587f, 0.114f));
}

float get_saturation(in float ma, in float mi) 
{
	if(ma == mi)
	{
		return 0.f;
	}
	else
	{
		float delta = ma - mi;
		float lightness = (ma + mi)/2.0f;
		float denom = (1.0f-abs(2.0f*lightness-1.0f));
		return 0.f == denom? 0.f : delta/denom;	
	}
}

float get_saturation(in vec3 color)
{
	float ma;
	float mi;
	get_max_and_min(color, ma, mi);
	return get_saturation(ma, mi);
}

float get_max_min_diff(in vec3 color)
{
	float ma;
	float mi;
	get_max_and_min(color, ma, mi);
	return ma-mi;
}

void get_max_and_min(in vec3 color, out float ma, out float mi)
{
	if(color.r > color.b)
	{
		if(color.b > color.g) //rbg	rbg
		{
			ma = color.r;
			mi = color.g;
		}
		else if(color.r > color.g) //rgb  rgb
		{
			ma = color.r;
			mi = color.b;
		}
		else //grb   grb
		{
			ma = color.g;
			mi = color.b;
		}
	}
	else
	{ 
		if(color.r > color.g) //brg  brg
		{
			ma = color.b;
			mi = color.g;
		}
		else if(color.b > color.g) //bgr  bgr
		{
			ma = color.b;
			mi = color.r;
		}
		else //gbr  gbr
		{
			ma = color.g;
			mi = color.r;
		}
	}
}


