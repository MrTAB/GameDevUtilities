uniform sampler2D texture0;

///////////////////////////////////////////////////////////////////////////////
//	Repository of shader utilities associated with greyscaling	
///////////////////////////////////////////////////////////////////////////////
//
//	Example in Main performs Hue shifting on each fragment so that its
//	hue matches the gl_Color.
//
///////////////////////////////////////////////////////////////////////////////

vec3 get_greyscale_of(in vec3 color);
vec4 get_greyscale_of(in vec4 color);
float get_luminosity(in vec3 color);
float get_saturation(in float ma, in float mi);
float get_saturation(in vec3 color);
void get_max_and_min(in vec3 color, out float ma, out float mi);
void get_maxpos_and_min(in vec3 color, out float ma, out float mi, out int maxpos);
void get_hsl(in vec3 color, out float h, out float s, out float l);
vec3 get_rgb(in float h, in float s, in float l);


void main()
{
	vec4 textureColor = texture2D(texture0,gl_TexCoord[0].st);

	float t_h;
	float t_s;
	float t_l;
	float c_h;
	float c_s;
	float c_l;

	get_hsl(textureColor.rgb, t_h, t_s, t_l);
	get_hsl(gl_Color.rgb, c_h, c_s, c_l);

	gl_FragColor.rgb = get_rgb(c_h, t_s, t_l);
	gl_FragColor.a = textureColor.a * gl_Color.a;
}


// Obtain Hue, Saturation and Lumination
//
void get_hsl(in vec3 c, out float h, out float s, out float l)
{
	float ma;
	float mi;
	int maxpos;
	get_maxpos_and_min(c, ma, mi, maxpos);

	l = (ma+mi)/2.0;

	if(ma == mi)
	{
		h = s = 0.0;
	}
	else
	{
		float d = ma - mi;
		s = l > 0.5 ? d / (2.0 - ma - mi) : d / (ma+mi);
		
		switch(maxpos)
		{
		  case 0: h = (c.g-c.b)/d + (c.g < c.b ? 6.0 : 0.0); break;
		  case 1: h = (c.b-c.r)/d + 2.0; break;
		  case 2: h = (c.r-c.g)/d + 4.0; break;
		}
		h = h/6.0;

	}
}

float hue2rgb(float p, float q, float t)
{
    if(t < 0.f) t += 1.f;
    if(t > 1.f) t -= 1.f;
    if(t < 1.f/6.f) return p + (q - p) * 6.f * t;
    if(t < 1.f/2.f) return q;
    if(t < 2.f/3.f) return p + (q - p) * (2.f/3.f - t) * 6.f;
    return p;
}

vec3 get_rgb(in float h, in float s, in float l)
{
	if(s == 0.f)
	{
		return vec3(l,l,l);
	}
	else
	{
		float q = l < 0.5f? l * (1.f + s) : l + s - l*s;
		float p = 2 * l - q;
        	return vec3(    hue2rgb(p, q, h + 1.f/3.f),
		   		hue2rgb(p, q, h),
        			hue2rgb(p, q, h - 1.f/3.f) );
	}
}



vec4 get_greyscale_of(in vec4 color)
{
	float luminosity = get_luminosity(color.rgb);
	return vec4(luminosity, luminosity, luminosity, color.a);
}

vec3 get_greyscale_of(in vec3 color)
{
	float luminosity = get_luminosity(color);
	return vec3(luminosity, luminosity, luminosity);
}

float get_luminosity(in vec3 color)
{
	return dot(color, vec3(0.299, 0.587, 0.114));
}

float get_saturation(in float ma, in float mi)
{
	if(ma == mi)
	{
		float delta = ma - mi;
		float lightness = (ma + mi)/2;
		return delta/(1.0-abs(2.0*lightness-1.0));	
	}
	else
	{
		return ma - mi;
	}
}

float get_saturation(in vec3 color)
{
	float ma;
	float mi;
	get_max_and_min(color, ma, mi);
	return get_saturation(ma, mi);
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

void get_maxpos_and_min(in vec3 color, out float ma, out float mi, out int maxpos)
{
	if(color.r > color.b)
	{
		if(color.b > color.g) //rbg	rbg
		{
			ma = color.r; maxpos = 0;
			mi = color.g;
		}
		else if(color.r > color.g) //rgb  rgb
		{
			ma = color.r; maxpos = 0;
			mi = color.b;
		}
		else //grb   grb
		{
			ma = color.g; maxpos = 1;
			mi = color.b;
		}
	}
	else
	{ 
		if(color.r > color.g) //brg  brg
		{
			ma = color.b; maxpos = 2;
			mi = color.g;
		}
		else if(color.b > color.g) //bgr  bgr
		{
			ma = color.b; maxpos = 2;
			mi = color.r;
		}
		else //gbr  gbr
		{
			ma = color.g; maxpos = 1;
			mi = color.r;
		}
	}
}



