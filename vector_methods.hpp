/*
*
*	vector_methods.hpp
*
*   Utility methods for working on vectors of two floats
*  
*   These utility methods were created in this format for work with the Box2D
*   physics engine, and thus Box2D is a dependency on this unit
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



#ifndef GAME_DEV_UTILITIES_VECTOR_METHODS_HPP
#define GAME_DEV_UTILITIES_VECTOR_METHODS_HPP
#include"floats.hpp"
#include<Box2D/Common/b2Math.h>
#include<cmath>
#include<cassert>
namespace game_dev_utilities
{
namespace vector
{
   

 

// Compare two vectors for equality, returning true if they are considered equal
// under this comparison
inline bool compare (const b2Vec2 &a,const b2Vec2 &b)
{
    return floats::compare(a.x,b.x) && floats::compare(a.y,b.y);
}

// Set the length of the vector. Vector itself must have non zero length
// Calling set_length on a zero length vector causes undefined behaviour.
inline void set_length (b2Vec2 &vector, const float length)
{
    assert(vector.LengthSquared() != 0);
    
    const float multiplier = length / vector.Length();
    vector *= multiplier;
}

// Returns the distance between the end points of two vectors
inline float distance(const b2Vec2 &a, const b2Vec2&b)
{
    return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

// Returns true if the vector is unit length.
inline bool is_unit_length (const b2Vec2 &vector)
{
    return floats::compare(vector.LengthSquared(),1.0f);
}

// Returns true if the vector has zero length.
// Note that this is distinct from being the pure zero vector b2Vec2_zero,
// as exact values of 0.f are unique from very small values close to zero
inline bool is_zero_length (const b2Vec2 &vector)
{
    return floats::is_zero(vector.x) && floats::is_zero(vector.y);
}

// Calculates the angle (in radians) of the vector from the positive x-axis
inline float get_angle (const b2Vec2 &vector)
{
    return std::atan2(vector.y,vector.x);
}

// Set the vector as having that angle (in radians) and length.
inline void set_angle_length (b2Vec2 &vector, const float radians, const float length)
{
    vector.Set(length*std::cos(radians),length*std::sin(radians));
}

// Set the angle of the vector to the given radians, maintaining length
inline void set_angle (b2Vec2 &vector, const float radians)
{
    const float length = vector.Length();
    vector.Set(length*std::cos(radians),length*std::sin(radians));
}

// ROtate the vector around the origin by the given radians
inline void rotate (b2Vec2 &vector, const float radians)
{
    set_angle (vector, get_angle(vector) + radians);
}

// Flip the vector
inline void invert(b2Vec2 &vector)
{
    vector.Set(-vector.x,-vector.y);
}

// efficiently turns vector pi/2 radians in the direction of the y axis to x axis
inline void turn_yx (b2Vec2 &vector)
{
    vector.Set(vector.y,-vector.x);
}

// efficiently turns vector pi/2 radians in the direction of the x axis to y axis
inline void turn_xy (b2Vec2 &vector)
{
    vector.Set(-vector.y,vector.x);
}

// Flip the vector about the x axis
inline void flip_about_x (b2Vec2 &vector)
{
    vector.y = -vector.y;
}

// Flip the vector about the y axis
inline void flip_about_y (b2Vec2 &vector)
{
    vector.x = -vector.x;
}

// Returns true if the length of a is greater than the length of b
// Due to the use of LenghtSquared() for efficiency, the granularity of the
// comparison is stretched meaning that there may exist a case where
// individual calculation of length above 1.0f could result in two values for
// whom the lengths return equal under compare(), and vice versa for values less
// than 1.0f. For the practical purposes for which this method has been devised,
// this is not a concern.
inline bool greater_than(const b2Vec2 &a, const b2Vec2 &b)
{
    return a.LengthSquared() > b .LengthSquared() && !compare(a,b);
}

// Returns true if the length of a is less than the length of b.
// See notes on granularity above.
inline bool less_than(const b2Vec2 &a, const b2Vec2 &b)
{
    return a.LengthSquared() < b .LengthSquared() && !compare(a,b);
}

// Returns true if the length of a is greater than the length of b, or if they
//   have equal length.
// See notes on granularity above.
inline bool greater_than_or_equal(const b2Vec2 &a, const b2Vec2 &b)
{
    return a.LengthSquared() >= b .LengthSquared() || !compare(a,b);
}

// Returns true if the length of a is less than the length of b, or if they have
//   equal lengths
// See notes on granularity above.
inline bool less_than_or_equal(const b2Vec2 &a, const b2Vec2 &b)
{
    return a.LengthSquared() <= b .LengthSquared() || !compare(a,b);
}

// Returns the larger lengthed of two vectors, defaulting to a if they are equal
inline b2Vec2 & largest (b2Vec2 &a, b2Vec2 &b)
{
    if (greater_than_or_equal (a,b))
    {
        return a;
    }
    else
    {
        return b;
    }
}

// Returns the smaller lengthed of two vectors, defaulting to a if they are equal
inline b2Vec2 & smallest (b2Vec2 &a, b2Vec2 &b)
{
    if (less_than_or_equal (a,b))
    {
        return a;
    }
    else
    {
        return b;
    }
}

// Linearly interpolates between vector a and b to the given ratio, and stores
// this in a
inline void interpolated (b2Vec2 &a, const b2Vec2 &b, const float ratio)
{
    const float inverse = 1.0/ratio;
    a.Set (ratio*b.x+inverse*a.x, ratio*b.y+inverse*a.y);
}

// Linearly interpolates between vector a and b to the given ratio, and returns
// this in c
inline b2Vec2 interpolate (b2Vec2 a, const b2Vec2 b, const float ratio)
{
    const float inverse = 1.0/ratio;
    b2Vec2 c;
    c.Set (ratio*b.x+inverse*a.x, ratio*b.y+inverse*a.y);
    return c;
}

// Returns true if the given vectors are perpendicular to each other
inline bool perpendicular_to (const b2Vec2 &a, const b2Vec2 &b)
{
    return floats::is_zero(b2Dot(a,b));
}




} // namespace vector
} // 
#endif // 


