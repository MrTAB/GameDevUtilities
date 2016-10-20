/*
*
*	choice_arrays.hpp
*
*   choice_array provides an array in which one object is currently "chosen" as
*   the active object. The choice_array instance can be treated as an object of 
*   the chosens type implicitly. Use increment and decrement operations to move 
*   the chosen instance onto the next item in the array. This wraps around to
*   the other end of the array at boundaries.
*
*   This can be useful for encapsulating the current item, choice, accessory etc
*   chosen by the player from a scrolling list of objects with unique behaviours.
*
*   choice_vector is a similar sort of object only with a vector container. As
*   public access is provided to the vector, care must be taken to not
*   invalidate the current chosen item through deletions. Future versions will
*   take this and several other things into account to produce an invalidation
*   safe choice_vector and choice_array by limiting access to the array and
*   index, and by checking and correcting the index when the vector reduces in
*   size.
*
*-------------------------------------------------------------------------------
*   Developer Notes:
*       These were made prior to C++11x and could be reviewed.
*       choice_vector
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



#ifndef GAME_DEV_UTILITIES_CHOICE_ARRAYS_HPP
#define GAME_DEV_UTILITIES_CHOICE_ARRAYS_HPP
#include<vector>
namespace game_dev_utilities
{


template<typename T, const unsigned int S>
struct choice_array_t
{
    T array[S];
    int index;
    
    choice_array_t() : index (0)
    {
        // nothing //
    }
    
    T & chosen()
    {
        return array[index];
    }
    
    const T & chosen() const
    {
        return array[index];
    }
    
    // set the subseqeunt item as 'chosen', looping back to the start once at the end
    void operator ++ ()
    {
        ++index;
        if (index >= S)
        {
            index = 0;
        }
    }
    
    // set the previous item as 'chosen', looping to the end if already at the first element
    void operator -- ()
    {
        --index;
        if (index < 0)
        {
            index = S - 1;
        }
    }
    
    void set (int index_in)
    {
        if (index_in >=0 && index_in < S)
        {
            index = index_in;
        }
    }

};


template<typename T>
struct choice_vector_t
{
    std::vector<T> array;
    int index;
    
    choice_vector_t() : index (0)
    {
        // nothing //
    }
    
    T & chosen()
    {
        return array[index];
    }
    
    const T & chosen() const
    {
        return array[index];
    }
    
    // set the subseqeunt item as 'chosen', looping back to the start once at the end
    void operator ++ ()
    {
        ++index;
        if (index >= array.size())
        {
            index = 0;
        }
    }
    
    // set the previous item as 'chosen', looping to the end if already at the first element
    void operator -- ()
    {
        --index;
        if (index < 0)
        {
            index = array.size() - 1;
        }
    }
    
    void set (int index_in)
    {
        if (index_in >=0 && index_in < array.size())
        {
            index = index_in;
        }
    }
    
    void clear()
    {
        index = 0;
        array.clear();
    }
    
};

} // namespace super_pixel_boy
#endif // GAME_DEV_UTILITIES_CHOICE_ARRAYS_HPP


