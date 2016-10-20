/*
*
*	angles.hpp
*
*   A set of utility methods for working with angles during
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



#ifndef GAME_DEV_UTILITIES_ANGLES_HPP
#define GAME_DEV_UTILITIES_ANGLES_HPP
#include"floats.hpp"
#ifdef ANGLES_TESTS
    #include<iostream>
    #include<sstream>
#endif
namespace game_dev_utilities
{
namespace angles
{

// convert radians to degrees
inline float radians_to_degrees (const float radians)
{
    return 180.0*radians/floats::pi;
}

// degrees to radians
inline float degrees_to_radians (const float degrees)
{
    return floats::pi*degrees/180.0;
}

// converts angle to range  [0,2pi)
inline float normalised_radians(float radians) 
{
    using floats::pi;
    
    while(radians >= pi/2.f)
    {
        radians -= 2.f*pi;
    }
    while(radians < 0.f)
    {
        radians += 2.f*pi;
    }
    return radians;
}

// converts angle to range (-pi,pi]
inline float angle_to_pirange(float radians) 
{
    using floats::pi;
    
    while(radians <= -pi)
    {
        radians += 2.f*pi;
    }
    while(radians > pi)
    {
        radians -= 2.f*pi;
    }
    return radians;
}

// accepts radians in any range
// returns in range [0,2*pi)
float clipped_to_right_angle(float radians);

// 'flip' the angle - works on angles in any range but does not preserve range
inline float invert(float radians)
{
    return radians + floats::pi;
}

// takes radians in pirange and maintains wihtin that range
inline float invert_pirange(float radians_in_pirange)
{
    radians_in_pirange += floats::pi;
    if(radians_in_pirange > floats::pi)
    {
        radians_in_pirange -= 2.f*floats::pi;
    }
    return radians_in_pirange;
}


// works for angles in range (-pi,pi]
inline float pirange_angle_difference(float a, float b)
{
	using floats::pi;

	float diff = b - a;
	diff += (diff > pi)? -2*pi : (diff < -pi)? 2*pi : 0;
	return diff;
}


// works for angles in any range
inline float angle_difference(float a, float b)
{	
	return pirange_angle_difference(angles::angle_to_pirange(a),
                                 angles::angle_to_pirange(b));   
}


// works for angles in range (-pi,pi]. returns 1, 0.f or -1
inline float pirange_angle_difference_sign(float a, float b)
{
	using floats::pi;

	float diff = b - a;
	diff += (diff > pi)? -2*pi : (diff < -pi)? 2*pi : 0;
	return (0.f < diff) - (diff < 0.f);
}


// works for angles in any range: return 1, 0.f or -1.
inline float angle_difference_sign(float a, float b)
{	
	return pirange_angle_difference_sign(angles::angle_to_pirange(a),
                                 angles::angle_to_pirange(b));  
}


inline int positive_modulo(int i, int n)
{
    return (i % n + n) % n;
}

// multiplies by the given granularity, clips to int, normalises using modulo,
// divides by granularity and returns radians in the range [0,2*pi)
// too large a granularity can lead to integer overflows.
inline float clipped_radians(float radians, unsigned int granularity = 524280)
{
    int deg = granularity *radians/floats::pi;
    
    deg = positive_modulo(deg, 2*granularity);
    
    return floats::pi*deg/(granularity);
}

// multiplies by the given granularity, clips to int, normalises using modulo,
// divides by granularity and returns radians at least in the range [-pi,pi]
// too large a granularity can lead to integer overflows.
inline float clipped_to_pirange(float radians, unsigned int granularity = 524280)
{
    int deg = granularity *radians/floats::pi;
    
    deg = positive_modulo(deg, 2*granularity);
    
    if(deg > granularity)
    {
        deg -= 2*granularity;
    }
    
    return floats::pi*deg/(granularity);
}



#ifdef ANGLES_TESTS


std::string float_to_string_in_radians(const float f);

void test_float_to_string_in_radians();

void test_normalised_radians();

void test_angle_to_pirange();



inline void test_clipped_radians();

void test_clipped_to_pirange();

#endif

}
}
#endif // GAME_DEV_UTILITIES_ANGLES_HPP


