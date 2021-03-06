/*
*
*	color.hpp
*
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


#ifndef GAME_DEV_UTILITIES_COLOR_HPP
#define GAME_DEV_UTILITIES_COLOR_HPP
#include<visen/color.hpp>
namespace game_dev_utilities
{
   
typedef uint8_t sample_t;

struct color_t
{
    sample_t red, green, blue, alpha;
    
    color_t(sample_t r, sample_t g, sample_t b):
        red(r),
        green(g),
        blue(b),
        alpha(255)
    {
        // done //
    }
    
    color_t(sample_t r, sample_t g, sample_t b, sample_t a):
        red(r),
        green(g),
        blue(b),
        alpha(a)
    {
        // done //
    }
};

namespace color_methods
{
    
struct hsl_t
{
    float h, s, l; // in range [0.f,1.f]
};

} 
} 
#endif // GAME_DEV_UTILITIES_COLOR_HPP


