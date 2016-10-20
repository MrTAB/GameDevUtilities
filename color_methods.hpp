/*
*
*	color_methods.hpp
*
*   methods for working with colors
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


#pragma once
#ifndef GAME_DEV_UTILITIES_COLOR_METHODS_HPP
#define GAME_DEV_UTILITIES_COLOR_METHODS_HPP
#include"color.hpp"
#include<algorithm>
#include<cassert>
namespace game_dev_utilities
{
namespace color_methods
{


inline
color_t add(const color_t a, const color_t b)
{
    return color_t(std::min(255, a.red   +  b.red),
                   std::min(255, a.green +  b.green)),
                   std::min(255, a.blue  +  b.blue)));
}

inline
color_t subtract(const color_t a, const color_t b)
{
    return color_t(std::max(0, a.red   -  b.red),
                   std::max(0, a.green -  b.green)),
                   std::max(0, a.blue  -  b.blue)));
}

inline
color_t addsubtract(const color_t a, int k)
{
    return color_t(std::max(0, std::min(255, a.red   +  k)),
                   std::max(0, std::min(255, a.green +  k)),
                   std::max(0, std::min(255, a.blue  +  k)));
}

inline
color_t add(const color_t a, sample_t k)
{
    return color_t(std::min(255, a.red   +  k),
                   std::min(255, a.green +  k),
                   std::min(255, a.blue  +  k));
}

inline
color_t subtract(const color_t a, sample_t k)
{
    return color_t(std::max(0, a.red   -  k),
                   std::max(0, a.green -  k),
                   std::max(0, a.blue  -  k));
}

inline
color_t inverted(const color_t c)
{
    return color_t(255-c.red,
                   255-c.green,
                   255-c.blue);
}



inline
color_t rgb_to_rbg(const color_t c)
{
    return color_t(c.red, c.blue, c.green);
}

inline
color_t rgb_to_grb(const color_t c)
{
    return color_t(c.green, c.red, c.blue);
}


inline
color_t rgb_to_gbr(const color_t c)
{
    return color_t(c.green, c.blue, c.red);
}


inline
color_t rgb_to_brg(const color_t c)
{
    return color_t(c.blue, c.red, c.green);
}


inline
color_t rgb_to_bgr(const color_t c)
{
    return color_t(c.blue, c.green, c.red);
}

inline
color_t rotated_right(const color_t c)
{
    return rgb_to_bgr(c);
}

inline
color_t rotated_left(const color_t c)
{
    return rgb_to_gbr(c);
}

color_t random_color();
color_t random_color(const color_t a, const color_t b);

hsl_t get_hsl(const color_t);

color_t get_color(const hsl_t hsl);

color_t get_greyscale(const color_t);

inline
color_t hue_changed(const color_t c, const float hue)
{
    assert(hue >= 0.f && hue <= 1.0f);
    hsl_t hsl = get_hsl(c);
    hsl.h = hue;
    return get_color(hsl);
}

inline
color_t saturation_changed(const color_t c, const float saturation)
{
    assert(saturation >= 0.f && saturation <= 1.0f);
    hsl_t hsl = get_hsl(c);
    hsl.s = saturation;
    return get_color(hsl);
}

inline
color_t lightness_changed(const color_t c, const float lumin)
{
    assert(lumin >= 0.f && lumin <= 1.0f);
    hsl_t hsl = get_hsl(c);
    hsl.l = lumin;
    return get_color(hsl);
}

inline
color_t hue_moved(const color_t c, const float change)
{
    hsl_t hsl = get_hsl(c);
    hsl.h = std::min(std::max(hsl.h + change, 0.f), 1.f);
    return get_color(hsl);
}

inline
color_t saturation_moved(const color_t c, const float change)
{
    hsl_t hsl = get_hsl(c);
    hsl.s = std::min(std::max(hsl.s + change, 0.f), 1.f);
    return get_color(hsl);
}

inline
color_t lightness_moved(const color_t c, const float change)
{
    hsl_t hsl = get_hsl(c);
    hsl.l = std::min(std::max(hsl.l + change, 0.f), 1.f);
    return get_color(hsl);
}




} // namespace color_methods
} 
#endif 


