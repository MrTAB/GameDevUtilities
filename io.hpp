/*
*
*    io.hpp - a series of short utilities for reading and writing to
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


#pragma once
#ifndef GAME_DEV_UTILITIES_IO_HPP
#define GAME_DEV_UTILITIES_IO_HPP
#include<iostream>
#include<sstream>
#include<stdexcept>
#include<fstream>
namespace game_dev_utilities
{

////////////////////////////////////////////////////////////////////////////////
/*//////////////////////////////////////////////////////////////////////////////

 Use these on files set up with std::ios::binary for cross platform binary reading.
 All other objects should be composed of units of these reads/writes or stream read/wite methods.
 A template is not offered as these types are only available based on their exact size.
 Make sure to read using std::ios::binary

*///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//  Read sized int
//////////////////////////////////////////////////////////////////////////////// 
    
inline std::istream& read(std::istream& in, int64_t&value)
{
    return in.read((char*)(&value),sizeof(int64_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, int32_t&value)
{
    return in.read((char*)(&value),sizeof(int32_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, int16_t&value)
{
    return in.read((char*)(&value),sizeof(int16_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, int8_t&value)
{
    return in.read((char*)(&value),sizeof(int8_t)/sizeof(char));
}

inline std::istream& read_s64(std::istream& in, int64_t&value)
{
    return in.read((char*)(&value),sizeof(int64_t)/sizeof(char));
}
inline std::istream& read_s32(std::istream& in, int32_t&value)
{
    return in.read((char*)(&value),sizeof(int32_t)/sizeof(char));
}
inline std::istream& read_s16(std::istream& in, int16_t&value)
{
    return in.read((char*)(&value),sizeof(int16_t)/sizeof(char));
}
inline std::istream& read_s8(std::istream& in, int8_t&value)
{
    return in.read((char*)(&value),sizeof(int8_t)/sizeof(char));
}

////////////////////////////////////////////////////////////////////////////////
//  Read sized unsigned int
//////////////////////////////////////////////////////////////////////////////// 
    
inline std::istream& read(std::istream& in, uint64_t&value)
{
    return in.read((char*)(&value),sizeof(uint64_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, uint32_t&value)
{
    return in.read((char*)(&value),sizeof(uint32_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, uint16_t&value)
{
    return in.read((char*)(&value),sizeof(uint16_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, uint8_t&value)
{
    return in.read((char*)(&value),sizeof(uint8_t)/sizeof(char));
}

inline std::istream& read_u64(std::istream& in, uint64_t&value)
{
    return in.read((char*)(&value),sizeof(uint64_t)/sizeof(char));
}
inline std::istream& read_u32(std::istream& in, uint32_t&value)
{
    return in.read((char*)(&value),sizeof(uint32_t)/sizeof(char));
}
inline std::istream& read_u16(std::istream& in, uint16_t&value)
{
    return in.read((char*)(&value),sizeof(uint16_t)/sizeof(char));
}
inline std::istream& read_u8(std::istream& in, uint8_t&value)
{
    return in.read((char*)(&value),sizeof(uint8_t)/sizeof(char));
}

////////////////////////////////////////////////////////////////////////////////
//  Read several sized ints
//////////////////////////////////////////////////////////////////////////////// 
    
inline std::istream& read(std::istream& in, int64_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(int64_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, int32_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(int32_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, int16_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(int16_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, int8_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(int8_t)/sizeof(char));
}


inline std::istream& read_s64(std::istream& in, int64_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(int64_t)/sizeof(char));
}
inline std::istream& read_s32(std::istream& in, int32_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(int32_t)/sizeof(char));
}
inline std::istream& read_s16(std::istream& in, int16_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(int16_t)/sizeof(char));
}
inline std::istream& read_s8(std::istream& in, int8_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(int8_t)/sizeof(char));
}

////////////////////////////////////////////////////////////////////////////////
//  Read several sized unsigned ints
//////////////////////////////////////////////////////////////////////////////// 
    
inline std::istream& read(std::istream& in, uint64_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(uint64_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, uint32_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(uint32_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, uint16_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(uint16_t)/sizeof(char));
}
inline std::istream& read(std::istream& in, uint8_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(uint8_t)/sizeof(char));
}

inline std::istream& read_u64(std::istream& in, uint64_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(uint64_t)/sizeof(char));
}
inline std::istream& read_u32(std::istream& in, uint32_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(uint32_t)/sizeof(char));
}
inline std::istream& read_u16(std::istream& in, uint16_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(uint16_t)/sizeof(char));
}
inline std::istream& read_u8(std::istream& in, uint8_t* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(uint8_t)/sizeof(char));
}


////////////////////////////////////////////////////////////////////////////////
//  Read sized string, max size 65535 chars
//////////////////////////////////////////////////////////////////////////////// 

// caller must delete allocated string with delete[]
inline std::istream& read_alloc(std::istream& in, char ** str)
{
    uint16_t size = 0;
    read(in,size);
    *str = new char [size];
    return in.read(*str, size * sizeof(char));
}

inline std::istream& read(std::istream& in, std::string &str)
{
    uint16_t size = 0;
    read(in,size);
    
    str.assign(size,' ');
    
    return in.read(&str[0], size * sizeof(char));
}

////////////////////////////////////////////////////////////////////////////////
//  Read float
//////////////////////////////////////////////////////////////////////////////// 
    
inline std::istream& read(std::istream& in, float&value)
{
    return in.read((char*)(&value),sizeof(float)/sizeof(char));
}
inline std::istream& read(std::istream& in, float* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(float)/sizeof(char));
}

inline std::istream& read_d(std::istream& in, double&value)
{
    return in.read((char*)(&value),sizeof(double)/sizeof(char));
}
inline std::istream& read_d(std::istream& in, double* values, const size_t count)
{
    return in.read((char*)(values), count * sizeof(double)/sizeof(char));
}

////////////////////////////////////////////////////////////////////////////////
//  Read bool
//////////////////////////////////////////////////////////////////////////////// 

inline std::istream& read(std::istream& in, bool&value)
{
    uint8_t buff;
    read(in, buff);
    value = buff;
    return in;
}

inline std::istream& read_b(std::istream& in, bool&value)
{
    uint8_t buff;
    read(in, buff);
    value = buff;
    return in;
}


std::istream& read(std::istream& in, bool* values, const size_t count);
inline std::istream& read_b(std::istream& in, bool* values, const size_t count)
{
    return read(in, values, count);
}



////////////////////////////////////////////////////////////////////////////////
//  Read several sized unknowns into a container of those unknowns (relies on other methods resolving as desired - does not work with doubles)
//////////////////////////////////////////////////////////////////////////////// 
template<typename C>
inline std::istream& read(std::istream& in, C & container)
{
    uint32_t size;
    game_dev_utilities::read(in, size);
    
    if (size)
    {
        typename C::value_type * value_buffer = new typename C::value_type[size];
        
        game_dev_utilities::read(in, value_buffer, size);
        container.insert(container.end(), value_buffer, value_buffer + size);
        
        delete[]value_buffer;
    }
   
    return in;
}


////////////////////////////////////////////////////////////////////////////////
//  Write sized int
//////////////////////////////////////////////////////////////////////////////// 
//todo - TO BE TESTED
inline std::ostream& write(std::ostream& out, const int64_t&value)
{
    return out.write((char*)(&value),sizeof(int64_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const int32_t&value)
{
    return out.write((char*)(&value),sizeof(int32_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const int16_t&value)
{
    return out.write((char*)(&value),sizeof(int16_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const int8_t&value)
{
    return out.write((char*)(&value),sizeof(int8_t)/sizeof(char));
}

inline std::ostream& write_s64(std::ostream& out, const int64_t&value)
{
    return out.write((char*)(&value),sizeof(int64_t)/sizeof(char));
}
inline std::ostream& write_s32(std::ostream& out, const int32_t&value)
{
    return out.write((char*)(&value),sizeof(int32_t)/sizeof(char));
}
inline std::ostream& write_s16(std::ostream& out, const int16_t&value)
{
    return out.write((char*)(&value),sizeof(int16_t)/sizeof(char));
}
inline std::ostream& write_s8(std::ostream& out, const int8_t&value)
{
    return out.write((char*)(&value),sizeof(int8_t)/sizeof(char));
}

////////////////////////////////////////////////////////////////////////////////
//  Write sized unsigned int
//////////////////////////////////////////////////////////////////////////////// 
//todo - TO BE TESTED
inline std::ostream& write(std::ostream& out, const uint64_t&value)
{
    return out.write((char*)(&value),sizeof(uint64_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const uint32_t&value)
{
    return out.write((char*)(&value),sizeof(uint32_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const uint16_t&value)
{
    return out.write((char*)(&value),sizeof(uint16_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const uint8_t&value)
{
    return out.write((char*)(&value),sizeof(uint8_t)/sizeof(char));
}

inline std::ostream& write_u64(std::ostream& out, const uint64_t&value)
{
    return out.write((char*)(&value),sizeof(uint64_t)/sizeof(char));
}
inline std::ostream& write_u32(std::ostream& out, const uint32_t&value)
{
    return out.write((char*)(&value),sizeof(uint32_t)/sizeof(char));
}
inline std::ostream& write_u16(std::ostream& out, const uint16_t&value)
{
    return out.write((char*)(&value),sizeof(uint16_t)/sizeof(char));
}
inline std::ostream& write_u8(std::ostream& out, const uint8_t&value)
{
    return out.write((char*)(&value),sizeof(uint8_t)/sizeof(char));
}


////////////////////////////////////////////////////////////////////////////////
//  Write several sized ints
//////////////////////////////////////////////////////////////////////////////// 
//todo - TO BE TESTED
inline std::ostream& write(std::ostream& out, const int64_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(int64_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const int32_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(int32_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const int16_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(int16_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const int8_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(int8_t)/sizeof(char));
}

inline std::ostream& write_s64(std::ostream& out, const int64_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(int64_t)/sizeof(char));
}
inline std::ostream& write_s32(std::ostream& out, const int32_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(int32_t)/sizeof(char));
}
inline std::ostream& write_s16(std::ostream& out, const int16_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(int16_t)/sizeof(char));
}
inline std::ostream& write_s8(std::ostream& out, const int8_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(int8_t)/sizeof(char));
}

////////////////////////////////////////////////////////////////////////////////
//  Write several sized unsigned ints
//////////////////////////////////////////////////////////////////////////////// 
//todo - TO BE TESTED
inline std::ostream& write(std::ostream& out, const uint64_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(uint64_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const uint32_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(uint32_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const uint16_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(uint16_t)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const uint8_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(uint8_t)/sizeof(char));
}


inline std::ostream& write_u64(std::ostream& out, const uint64_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(uint64_t)/sizeof(char));
}
inline std::ostream& write_u32(std::ostream& out, const uint32_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(uint32_t)/sizeof(char));
}
inline std::ostream& write_u16(std::ostream& out, const uint16_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(uint16_t)/sizeof(char));
}
inline std::ostream& write_u8(std::ostream& out, const uint8_t* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(uint8_t)/sizeof(char));
}


////////////////////////////////////////////////////////////////////////////////
//  Write sized string, max size 65535 chars
//////////////////////////////////////////////////////////////////////////////// 

inline std::ostream& write(std::ostream& out, const char * str, const uint16_t size)
{
    write(out, size);
    return out.write(str, size * sizeof(char));
}

inline std::ostream& write(std::ostream& out, const std::string str)
{
    uint16_t size = str.size();
    write(out, size);
    return out.write(str.c_str(), size * sizeof(char));
}

////////////////////////////////////////////////////////////////////////////////
//  Write float
//////////////////////////////////////////////////////////////////////////////// 
//todo - TO BE TESTED
inline std::ostream& write(std::ostream& out, const float&value)
{
    return out.write((char*)(&value),sizeof(float)/sizeof(char));
}
inline std::ostream& write(std::ostream& out, const float* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(float)/sizeof(char));
}

inline std::ostream& write_d(std::ostream& out, const double&value) //todo  -remove _d specification
{
    return out.write((char*)(&value),sizeof(double)/sizeof(char));
}
inline std::ostream& write_d(std::ostream& out, const double* values, const size_t count)
{
    return out.write((char*)(values), count * sizeof(double)/sizeof(char));
}

////////////////////////////////////////////////////////////////////////////////
//  Write bools
//////////////////////////////////////////////////////////////////////////////// 

inline std::ostream& write(std::ostream& out, const bool&value)
{
    uint8_t buff = value;
    return write(out, buff);
}

inline std::ostream& write_b(std::ostream& out, const bool&value)
{
    uint8_t buff = value;
    return write(out, buff);
}

std::ostream& write(std::ostream& out, const bool* values, const size_t count);
inline std::ostream& write_b(std::ostream& out, const bool* values, const size_t count)
{
    return write(out, values, count);
}


////////////////////////////////////////////////////////////////////////////////
//  Write several sized unknowns from a container (relies on other methods)
//////////////////////////////////////////////////////////////////////////////// 
template<typename C>
inline std::ostream& write(std::ostream& out, const C & container)
{
    game_dev_utilities::write(out, static_cast<uint32_t>(container.size()));
    if (! container.empty())
    {
        game_dev_utilities::write(out, &container[0], container.size());
    }
    return out;
}


////////////////////////////////////////////////////////////////////////////////
//  To String method
//////////////////////////////////////////////////////////////////////////////// 

template<typename T>
inline std::string to_string(T t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}


////////////////////////////////////////////////////////////////////////////////
//  From String method
//////////////////////////////////////////////////////////////////////////////// 

class conversion_error : public std::invalid_argument
{
    public:
    
    explicit conversion_error(const std::string& what_arg) : invalid_argument(what_arg)
    {
        // do nothing //
    }
};

template<typename T>
inline T from_string(const std::string& str)
{
    std::istringstream iss(str);
    T t;

    iss >> std::ws >> t >> std::ws;

    if(!iss.eof())
    {
        throw conversion_error("stdaab::from_string::\tInvalid argument, failed to convert string to required type.");
    }

    return t; 
}

template<typename T>
inline T from_string_no_throw(const std::string& str, T value_if_error)
{
    std::istringstream iss(str);
    T t;

    iss >> std::ws >> t >> std::ws;

    if(!iss.eof())
    {
        return value_if_error;
    }

    return t; 
}


inline void copy_file_to_string(std::ifstream&file, std::string&string)
{
    file.seekg(0,std::ios::end);
    string.reserve(file.tellg());
    file.seekg(0,std::ios::beg);
    string.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());    
}




} // namespace game_dev_utilities
#endif // GAME_DEV_UTILITIES_IO_HPP

