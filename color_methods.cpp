/*
*
*	color_methods.cpp
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



#include"color_methods.hpp"
namespace game_dev_utilities
{
namespace color_methods
{


struct max_of_3_t
{
    float value;
    unsigned int pos;
    
    explicit max_of_3_t(const float a, const float b, const float c)
    {
        if(a > b)
        {
            if(a > c)
            {
                value = a;
                pos = 0;
            }
            else
            {
                value = c;
                pos = 2;
            }
        }
        else
        {
            if(b > c)
            {
                value = b;
                pos = 1;
            }
            else
            {
                value = c;
                pos = 2;
            }
        }
    }
    
    operator float()const
    {
        return value;
    }
    
    operator float&()
    {
        return value;
    }
};

struct min_of_3_t
{
    float value;
    unsigned int pos;
    
    explicit min_of_3_t(const float a, const float b, const float c)
    {
        if(a < b)
        {
            if(a < c)
            {
                value = a;
                pos = 0;
            }
            else
            {
                value = c;
                pos = 2;
            }
        }
        else
        {
            if(b < c)
            {
                value = b;
                pos = 1;
            }
            else
            {
                value = c;
                pos = 2;
            }
        }
    }
    
    operator float()const
    {
        return value;
    }
    
    operator float&()
    {
        return value;
    }
};

hsl_t get_hsl(const color_t c)
{
    const float r = (float)c.red / 255.f;
    const float g = (float)c.green / 255.f;
    const float b = (float)c.blue / 255.f;
    
    const max_of_3_t max(r,g,b);
    const min_of_3_t min(r,g,b); // optimize - do not need a min pos finder.
    
    hsl_t hsl;
    hsl.l = (max + min)/2.f;
    
    if(max == min)
    {
        hsl.h = hsl.s = 0;
    }
    else
    {
        const float d = max - min;
        hsl.s =  hsl.l > 0.5f ? d / (2.f - max - min) : d / (max + min);
        switch(max.pos)
        {
            case 0: hsl.h = (g - b) / d + (g < b ? 6.f : 0); break;
            case 1: hsl.h = (b - r) / d + 2.f; break;
            case 2: hsl.h = (r - g) / d + 4.f; break;
        }
        hsl.h /= 6.f;
    }
    
    return hsl;
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

color_t get_color(const hsl_t hsl)
{
    float r, g, b;
    
    if(hsl.s == 0.f)
    {
        r = g = b = hsl.l;
    }
    else
    {
        const float q = hsl.l < 0.5f ? hsl.l * (1.f + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s; 
        const float p = 2 * hsl.l - q;
        r = hue2rgb(p, q, hsl.h + 1.f/3.f);
        g = hue2rgb(p, q, hsl.h);
        b = hue2rgb(p, q, hsl.h - 1.f/3.f);
    }
    
    return color_t(255*r, 255*g, 255*b);
}

color_t get_greyscale(const color_t c)
{
    // CCIR601 luma
    const float luma = 0.299f*c.red + 0.587f*c.green + 0.114f*c.blue;
    return color_t(luma, luma, luma, alpha(c));
}


struct max_t
{
    float value;
    
    explicit max_t(const float v):value(v) { }
    
    max_t & operator,(const float f)
    {
        if (f > value) value = f;
        return *this;
    }
    
    static void test()
    {
        max_t(4),5,6,7,8,9;
    }
};


//todo - make methods to get saturation and lightness without having to calculate hsl
    

} // namespace color_methods
} // namespace super_pixel_boy

