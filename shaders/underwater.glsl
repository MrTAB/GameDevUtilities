uniform sampler2D texture0;		// The texture being oscillated
uniform float offsetx;			// initialized with 0.f
uniform float offsety;			// initialized with 0.f
const float textureWidth = 1024;	// full width of texture being oscillated
const float textureHeight = 1024;	// full height of texture being oscillated

///////////////////////////////////////////////////////////////////////////////
//	Underwater shader
///////////////////////////////////////////////////////////////////////////////
//
// This shader worbles sprites to simulate an underwater effect.
// A counter should be incremented during each game loop.
// offsetx and offset y should then be set to the value of the counter.
//
// Please note the set width and height above; could extend this shader to
// accept texture width and height.
//
///////////////////////////////////////////////////////////////////////////////


void main()
{
	vec2 textCoord = gl_TexCoord[0].st;
	textCoord.s = textCoord.s + 1.0/textureWidth.0 * sin(0.5f*(gl_FragCoord.x + offsetx));
	textCoord.t = textCoord.t + 1.0/textureHeight.0 * sin(0.5f*(gl_FragCoord.y + offsety));
	gl_FragColor = gl_Color*texture2D(texture0, textCoord);
}
