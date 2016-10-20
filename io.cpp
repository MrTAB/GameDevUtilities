/*

*    io.cpp - a series of short utilities for reading and writing to
*    binary files in C++
*
*    Used in saving specific fields to produce game save state files
*
--------------------------------------------------------------------------------

MIT License

Copyright (c) 2016 Antony Alastair Brown, MrTAB on GitHub

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
#include"io.hpp"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<stdexcept>
#include<limits>
namespace game_dev_utilities
{

std::istream& read(std::istream& in, bool* values, const size_t bitcount)
{
    const unsigned int byte_count = bitcount/8 + (bitcount%8 && true);
    const bool*end = values + bitcount;
    
    for(unsigned int t = 0; t < byte_count; ++t)
    {
        uint8_t bitbyte = 0;
        read(in, bitbyte);
        
        for(unsigned int b = 0; b < 8; ++b)
        {
            if(end == values)
            {
                break;
            }
            *values = (bitbyte >> b) & 1;
            ++values;
        }
    }
    
    return in;
}


std::ostream& write(std::ostream& out, const bool* values, const size_t count)
{
    const unsigned int byte_count = count/8 + (count%8 && true);
    bool const* itr = values;
    const bool * end = values + count;
    
    for(unsigned int t = 0; t < byte_count; ++t)
    {
        uint8_t bitbyte = 0;
        
        for(unsigned int b = 0; b < 8; ++b)
        {
            if(end == itr)
            {
                break;
            }
            bitbyte |= (*itr) << b;
            ++itr;
        }
        
        write(out, bitbyte);
    }
    
    return out;
}


}
