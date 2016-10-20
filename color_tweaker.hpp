/*
*
*	color_tweaker.hpp
*
*   An object which adjusts a color with respect to another color.
*   Subclasses provide different ways for a color to be tweaked in a way that
*   is interdependent from the object using the continuously adjusting colour.
*   Use for blending projectiles, enemies phasing colour during damage,
*   environments changing etc.
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


#ifndef GAME_DEV_UTILITIES_COLOR_TWEAKER_HPP
#define GAME_DEV_UTILITIES_COLOR_TWEAKER_HPP
#include"color.hpp"
namespace game_dev_utilities
{

struct color_tweaker_t
{
    virtual ~color_tweaker_t()
    {
        //do nothing //
    };
    
    virtual void tweak_color(color_t&color) = 0;
};

struct blend_color_tweaker_t: public color_tweaker_t
{
    blend_color_tweaker_t():ratio(0.5f)
    {
        // do nothing //
    }
    
    color_t target;
    float ratio;
    
    virtual void tweak_color(color_t&color)
    {
        color.red = (ratio * color.red + (1.0f - ratio) * target.red);
        color.green = (ratio * color.green + (1.0f - ratio) * target.green);
        color.blue = (ratio * color.blue + (1.0f - ratio) * target.blue);
        color.alpha = (ratio * color.alpha + (1.0f - ratio) * target.alpha);
    }
};

struct sample_blend_color_tweaker_t: public color_tweaker_t
{
    sample_blend_color_tweaker_t():
     r_ratio(0.5f),
     g_ratio(0.5f),
     b_ratio(0.5f),
     a_ratio(0.5f)
    {
        // do nothing //
    }
        
    color_t target;
    float r_ratio;
    float g_ratio;
    float b_ratio;
    float a_ratio;
    
    virtual void tweak_color(color_t&color)
    {
        color.red = (r_ratio * color.red + (1.0f - r_ratio) * target.red);
        color.green = (g_ratio * color.green + (1.0f - g_ratio) * target.green);
        color.blue = (b_ratio * color.blue + (1.0f - b_ratio) * target.blue);
        color.alpha = (a_ratio * color.alpha + (1.0f - a_ratio) * target.alpha);
    }
};



} //  
#endif // 


