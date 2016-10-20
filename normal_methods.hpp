/*
*
*	normal_methods.hpp
*
*   A set of utility methods for working with normals during 2d game development
*   Normals supplied should be unit length.
*
--------------------------------------------------------------------------------
MIT License

Copyright (c) 2016 Tony Alastair Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 
*/




#ifndef GAME_DEV_UTILITIES_NORMAL_METHODS_HPP
#define GAME_DEV_UTILITIES_NORMAL_METHODS_HPP
#include"floats.hpp"
namespace game_dev_utilities
{
namespace normal
{
    
// 
// todo - test edge cases


////////////////////////////////////////////////////////////////////////////////
//  Methods for determining the "half" that a normal is within
////////////////////////////////////////////////////////////////////////////////

inline bool in_right_half (const float x, const float y)
{
    return x > 0;
}

inline bool in_left_half (const float x, const float y)
{
    return x < 0;
}

inline bool in_top_half (const float x, const float y)
{
    return y < 0;
}

inline bool in_bottom_half (const float x, const float y)
{
    return y > 0;
}

////////////////////////////////////////////////////////////////////////////////
//  Methods for determining the quadrant that a normal is within (axis aligned)
////////////////////////////////////////////////////////////////////////////////

inline bool in_topright_quadrant (const float x, const float y)
{
    return y <= 0 && x > 0;
}

inline bool in_bottomright_quadrant (const float x, const float y)
{
    return y >= 0 && x > 0;
}

inline bool in_bottomleft_quadrant (const float x, const float y)
{
    return y > 0 && x <= 0;
}

inline bool in_topleft_quadrant (const float x, const float y)
{
    return y <= 0 && x < 0;
}

////////////////////////////////////////////////////////////////////////////////
//  Methods for determining the quadrant that a normal is within (offset by pi/4)
//  These are useful for players and enemies using normals for "scoping"
//  directionally
////////////////////////////////////////////////////////////////////////////////

inline bool in_right_quadrant (const float x, const float y)
{
    return x > floats::invsqrt_2;
}

inline bool in_bottom_quadrant (const float x, const float y)
{
    return y > floats::invsqrt_2;
}

inline bool in_left_quadrant (const float x, const float y)
{
    return x < -floats::invsqrt_2;
}

inline bool in_top_quadrant (const float x, const float y)
{
    return y < -floats::invsqrt_2;
}

// "on" methods : checks edge with certainty
inline bool on_top_quadrant (const float x, const float y)
{
    return y < -floats::invsqrt_2 || floats::compare (y,-floats::invsqrt_2);
}

////////////////////////////////////////////////////////////////////////////////
//  Methods for determining the quadrant that an angle is within (offset by pi/4)
//  These are useful for players and enemies using normals for "scoping"
//  directionally
// works for radians in range 0 to 2 PI
////////////////////////////////////////////////////////////////////////////////
inline bool in_right_quadrant (const float radians)
{
    return (radians >= -0.25f*floats::pi && radians < 0.25f*floats::pi)
        || (radians >= 1.75f*floats::pi && radians < 2.25f*floats::pi);
}
inline bool in_bottom_quadrant (const float radians)
{
    return radians >= 0.25f*floats::pi && radians < 0.75f*floats::pi;
}
inline bool in_left_quadrant (const float radians)
{
    return radians >= 0.75f*floats::pi && radians < 1.25f*floats::pi;
}
inline bool in_top_quadrant (const float radians)
{
    return radians >= 1.25f*floats::pi && radians < 1.75f*floats::pi;
}

// convert angles [-pi,pi] to [0,2PI]
inline float plus_minus_pi_to_positive_pi(const float radians)
{
    return radians < 0? radians + 2*floats::pi : radians;
}

////////////////////////////////////////////////////////////////////////////////
//  Quadrant enumerate and associated methods
////////////////////////////////////////////////////////////////////////////////

enum quadrant_t
{
    RIGHT_QUADRANT = 0,
    BOTTOM_QUADRANT,
    LEFT_QUADRANT,
    TOP_QUADRANT
};


// Returns quadrant from normal as 0-3, where order goes right bottom left top
inline quadrant_t get_quadrant (const float x, const float y) 
{
    if (in_right_quadrant(x,y))
    {
        return RIGHT_QUADRANT;
    }
    else if (in_bottom_quadrant(x,y))
    {
        return BOTTOM_QUADRANT;
    }
    else if (in_left_quadrant(x,y))
    {
        return LEFT_QUADRANT;
    }
    else
    {
        return TOP_QUADRANT;
    }
}

// Returns quadrant from angle as 0-3, where order goes right bottom left top
// works for radians in range 0 to 2 PI
inline quadrant_t get_quadrant (const float radians) 
{
    if (in_right_quadrant(radians))
    {
        return RIGHT_QUADRANT;
    }
    else if (in_bottom_quadrant(radians))
    {
        return BOTTOM_QUADRANT;
    }
    else if (in_left_quadrant(radians))
    {
        return LEFT_QUADRANT;
    }
    else
    {
        return TOP_QUADRANT;
    }
}


////////////////////////////////////////////////////////////////////////////////
// Octant methods
////////////////////////////////////////////////////////////////////////////////

//
//  Methods for determining the Octant that a normal is within
//
//  Octants are labelled 0 to 7 as the angle of normals within that octant increase
//  i.e.
/*
        5   6
        
    4           7
    
    3           0
    
        2   1
        
// Please note the y axis is positive in the down direction in this diagram as
// common in 2d game development
*/


inline bool in_octant_0 (const float x, const float y)
{
    return y >= 0 && x > floats::invsqrt_2;
}

inline bool in_octant_1 (const float x, const float y)
{
    return y >= floats::invsqrt_2 && x > 0;
}

inline bool in_octant_2 (const float x, const float y)
{
    return y > floats::invsqrt_2 && x <= 0;
}

inline bool in_octant_3 (const float x, const float y)
{
    return y > 0 && x <= -floats::invsqrt_2;
}
inline bool in_octant_4 (const float x, const float y)
{
    return y <= 0 && x < -floats::invsqrt_2;
}

inline bool in_octant_5 (const float x, const float y)
{
    return y <= -floats::invsqrt_2 && x < 0;
}

inline bool in_octant_6 (const float x, const float y)
{
    return y < -floats::invsqrt_2 && x >= 0;
}

inline bool in_octant_7 (const float x, const float y)
{
    return y < 0 && x >= floats::invsqrt_2;
}

inline bool in_octant(const float x, const float y, const int number)
{
    switch(number)
    {
        case 0: return in_octant_0(x,y);
        case 1: return in_octant_1(x,y);
        case 2: return in_octant_2(x,y);
        case 3: return in_octant_3(x,y);
        case 4: return in_octant_4(x,y);
        case 5: return in_octant_5(x,y);
        case 6: return in_octant_6(x,y);
        case 7: return in_octant_7(x,y);
        default: return false;
    }
}

}   //  namespace normal
} //  
#endif // 


