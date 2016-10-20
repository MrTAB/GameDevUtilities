/*
*
*	floats.hpp
*
*   Utilities for working with floats in a more reliable manner during game
*   development
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



#ifndef GAME_DEV_UTILITIES_FLOATS_HPP
#define GAME_DEV_UTILITIES_FLOATS_HPP
#include<cmath>
#include<limits>
#include<algorithm>
namespace game_dev_utilities
{
    template<typename T>
    inline T set_min(T&a, const T b)
    {
        if (a < b)
        {
            a = b;
        }
        return a;
    }

    template<typename T>
    inline T set_max(T&a, const T b)
    {
        if (a > b)
        {
            a = b;
        }
        return a;
    }
}

namespace game_dev_utilities
{
namespace floats
{

static const float pi = 3.14159265358979f;
static const float half_pi = pi/2.f;
static const float quarter_turn_radians = pi/2.f;
static const float half_turn_radians = pi;
static const float invsqrt_2 = 0.70710678118f;

// Syntactic sugar for dividing non floats for a float result
template<typename T>
inline float divide(T a, T b)
{
    return static_cast<float>(a)/static_cast<float>(b);
}

// Syntactic sugar for dividing mixed non floats for a float result
template<typename A,typename B>
inline float divide(A a, B b)
{
    return static_cast<float>(a)/static_cast<float>(b);
}



// Compares floats with vectors in a 2d game space in mind. This will be less
// effective at comparison for larger numbers beyond the expected scope of
// the vectors, such as tens of thousands and up.
// should do fine for comparing anything above 1e-5 to 0
// returns true if they are considered equal under this comparison
inline bool compare (const float a, const float b)
{
    return std::fabs(a-b) < 1e-5; 
}

// Compares floats to zero with vectors in a 2d game space in mind; thus values
// appreciably close to zero are truncated.
inline bool is_zero(const float a)
{
    return std::fabs(a) < 1e-5;
}

// Relative comparison of two floating points that is suitable for a wider range of numbers
// returns true if they are considered equal under this comparison
inline bool compare_rel(const float a, const float b)
{
    using std::fabs;
    return fabs (a - b) <= std::max(fabs(a),fabs(b)) * std::numeric_limits<double>::epsilon ();
}


// Where a float is considered a one dimensional displacement from zero,
// this returns the smaller of that float and a given length
inline float min_length(const float a, const float min_len) // where min_len is positive
{
	return a < 0? std::max(a,-min_len) : std::min(a,min_len);
}

// Where a float is considered a one dimensional displacement from zero,
// this returns the larger of that float and a given length
inline float max_length(const float a, const float max_len)// where max_len is positive
{
	return a < 0? std::min(a,-max_len) : std::max(a,max_len);
}

// Where a float is considered a one dimensional displacement from zero, this
// returns the longest length of the two given displacements with its original
// sign intact
inline float maxabs(const float a, const float b)
{
	return std::fabs(a) > std::fabs(b) ? a : b;
}

// Where a float is considered a one dimensional displacement from zero, this
// returns the shortest length of the two given displacements with its original
// sign intact
inline float minabs(const float a, const float b)
{
	return std::fabs(a) < std::fabs(b) ? a : b;
}


} // namespace floats
} //  
#endif // 


