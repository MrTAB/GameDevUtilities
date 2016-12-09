uniform sampler2D texture0;		// The texture being oscillated
uniform float offsetx;			// initialized with 0.f
uniform float offsety;			// initialized with 0.f
const float textureWidth = 1024;	// full width of texture being oscillated
const float textureHeight = 1024;	// full height of texture being oscillated

///////////////////////////////////////////////////////////////////////////////
//	Shade enemy worble shader
///////////////////////////////////////////////////////////////////////////////
//
// This shader oscillates and worbles surfaces, and is used for an ethereal
// and spooky effect for the ghost like shade enemies in "The Edge of Shadow". 
// A counter is incremented during each game loop.
// offsetx is set to the value of the counter.
// offsety is set to the (counter%300)
// The result is a dynamic and changing worble effect
//
// Please note the set width and height above; could extend this shader to
// accept texture width and height.
//
///////////////////////////////////////////////////////////////////////////////


void main()
{
	vec2 textCoord = gl_TexCoord[0].st;

	if(offsety > 100)
	{
		textCoord.s = textCoord.s + 1.0/textureWidth * sin(0.5f*(gl_FragCoord.y + offsetx));
		textCoord.t = textCoord.t + 1.0/textureHeight * sin(0.5f*(gl_FragCoord.x + offsetx));
	}
	else
	{
		textCoord.s = textCoord.s + 1.0/textureWidth * sin(0.5f*(gl_FragCoord.x + offsetx));
		textCoord.t = textCoord.t + 1.0/textureHeight * sin(0.5f*(gl_FragCoord.y + offsetx));
	}
	gl_FragColor = gl_Color*texture2D(texture0, textCoord);
}


