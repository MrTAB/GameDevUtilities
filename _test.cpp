/*
*
*    _test.cpp - In progress testbed for this library
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

#include"_test.hpp"
#include"io.hpp"
#include<maths/random.hpp>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<stdexcept>
#include<limits>
namespace game_dev_utilities
{

////////////////////////////////////////////////////////////////////////////////
//  Random methods
////////////////////////////////////////////////////////////////////////////////

/*
*   These are used to generate test data
*   They are dated prior C++11x and thus while functional do nto take advantage
*   of the modern standard library approach for random number generation.
*/

int random (); // [0, 32767]
double randomReal (); // [0,1]
void seed_random (unsigned int);

int random (int n); // random 1 to n INCLUSIVE
int random (int a, int b);
long int random (long int a, long int b);
long long int random (long long int a, long long int b);
unsigned int random (unsigned int n); // random 1 to n INCLUSIVE
unsigned int random (unsigned int a, unsigned int b);
unsigned long int random (long unsigned int a, long unsigned int b);
unsigned long long int random (long long unsigned int a, long long unsigned int b);
double random (double n);
double random (double a, double b);
float random (float n);
float random (float a, float b);

int random_sign(); // returns -1 or 1

char randomAtoZ ();
char randomatoz ();
char random1to9 ();
char randomWellFormed();

bool random1in (int n); // e.g. random1in(5) is likely to return true 1/5th fo the time randomly
bool randomMinN (int m, int n);


////////////////////////////////////////////////////////////////////////////////
//  Utilities for generating test data
////////////////////////////////////////////////////////////////////////////////


void fill_string_collection(std::vector<std::string> & collection, const unsigned int fill_count)
{
    std::string buffer;
    buffer.reserve(1024);
    
    for (unsigned int str = 0; str < fill_count; ++str)
    {
        unsigned int strsize = random(1024-1);
        
        unsigned int ctr = 0;
        buffer.resize(strsize);
        for (; ctr < strsize; ++ctr)
        {
            buffer[ctr] = randomWellFormed(); 
        }
        
        if (buffer.size() != strsize)
        {
            throw std::logic_error ("stdaab::fill_string_collection:: error in string writing algorithm.");
        }
        
        collection.push_back(buffer);
    }
}

template<typename T>
void fill_collection(std::vector<T> & collection, const unsigned int fill_count)
{
    for (unsigned int t = 0; t < fill_count; ++t)
    {
        collection.push_back(random(std::numeric_limits<T>::min()/2.1,std::numeric_limits<T>::max()/2.1));
    }
    collection.push_back(std::numeric_limits<T>::min());
    collection.push_back(std::numeric_limits<T>::max());
    collection.push_back(std::numeric_limits<T>::min()+std::numeric_limits<T>::max()/2.0);
}

template<typename T>
void write_collection(std::ostream&out, const std::vector<T> & collection)
{
    for (typename std::vector<T>::const_iterator itr = collection.begin(); itr!=collection.end();++itr)
    {
        game_dev_utilities::write(out, *itr);
    }
}



template<typename C>
unsigned int comparative_read(std::istream&in, const C & collection)
{
    unsigned int matches = 0;
    for (typename C::const_iterator itr = collection.begin(); itr!=collection.end();++itr)
    {
        typename C::value_type buffer;
        game_dev_utilities::read(in, buffer);
        matches += (*itr == buffer );
    }
    return matches;
}

////////////////////////////////////////////////////////////////////////////////
//  Test method
////////////////////////////////////////////////////////////////////////////////

void run_test()
{
    
    const char test_filename[] = "stdaab_test";
    
    std::vector<std::string> strings; 
    std::vector<int64_t> int64s;
    std::vector<int32_t> int32s;
    std::vector<int16_t> int16s;
    std::vector<uint64_t> uint64s;
    std::vector<uint32_t> uint32s;
    std::vector<uint16_t> uint16s;    
    std::vector<float> floats; 
    
    fill_string_collection(strings,32);
    fill_collection(int64s, 128); 
    fill_collection(int32s, 128); 
    fill_collection(int16s, 128); 
    fill_collection(uint64s, 128); 
    fill_collection(uint32s, 128); 
    fill_collection(uint16s, 128); 
    fill_collection(floats, 128); 
    
    {
        std::ofstream out(test_filename, std::ios::binary);
        
        write_collection(out, strings);
        write_collection(out, int64s);
        write_collection(out, int32s);
        write_collection(out, int16s);
        write_collection(out, uint64s);
        write_collection(out, uint32s);
        write_collection(out, uint16s);    
        write_collection(out, floats);    
        write(out, int64s);
        write(out, int32s);
        write(out, int16s);
        write(out, uint64s);
        write(out, uint32s);
        write(out, uint16s);
        write(out, floats);
        out.close();
    }
    
    
    {
        std::ifstream in(test_filename, std::ios::binary);

        
        std::cout << "Comparing stored strings: " << comparative_read(in, strings)
            << " out of " << strings.size() << " successfully matched." << std::endl;        
        std::cout << "Comparing stored int64s: " << comparative_read(in, int64s)
            << " out of " << int64s.size() << " successfully matched." << std::endl;
        std::cout << "Comparing stored int32s: " << comparative_read(in, int32s)
            << " out of " << int32s.size() << " successfully matched." << std::endl;
        std::cout << "Comparing stored int16s: " << comparative_read(in, int16s)
            << " out of " << int16s.size() << " successfully matched." << std::endl;
        std::cout << "Comparing stored uint64s: " << comparative_read(in, uint64s)
            << " out of " << uint64s.size() << " successfully matched." << std::endl;
        std::cout << "Comparing stored uint32s: " << comparative_read(in, uint32s)
            << " out of " << uint32s.size() << " successfully matched." << std::endl;
        std::cout << "Comparing stored uint16s: " << comparative_read(in, uint16s)
            << " out of " << uint16s.size() << " successfully matched." << std::endl;
        std::cout << "Comparing stored floats: " << comparative_read(in, floats)
            << " out of " << floats.size() << " successfully matched." << std::endl;
        
        {
            std::vector<int64_t> int64s_copy;
            std::vector<int32_t> int32s_copy;
            std::vector<int16_t> int16s_copy;
            std::vector<uint64_t> uint64s_copy;
            std::vector<uint32_t> uint32s_copy;
            std::vector<uint16_t> uint16s_copy;    
            std::vector<float> floats_copy;

            read(in, int64s_copy);
            read(in, int32s_copy);
            read(in, int16s_copy);
            read(in, uint64s_copy);
            read(in, uint32s_copy);
            read(in, uint16s_copy);
            read(in, floats_copy);
            
            std::cout << "Comparing vector stored int64s: "
                << (int64s == int64s_copy? "Matched.":"Match Failed.") << std::endl;
            std::cout << "Comparing vector stored int32s: "
                << (int32s == int32s_copy? "Matched.":"Match Failed.") << std::endl;
            std::cout << "Comparing vector stored int16s: "
                << (int16s == int16s_copy? "Matched.":"Match Failed.") << std::endl;
            std::cout << "Comparing vector stored uint64s: "
                << (uint64s == uint64s_copy? "Matched.":"Match Failed.") << std::endl;
            std::cout << "Comparing vector stored uint32s: "
                << (uint32s == uint32s_copy? "Matched.":"Match Failed.") << std::endl;
            std::cout << "Comparing vector stored uint16s: "
                << (uint16s == uint16s_copy? "Matched.":"Match Failed.") << std::endl;
            std::cout << "Comparing vector stored floats: "
                << (floats == floats_copy? "Matched.":"Match Failed.") << std::endl;
        }
        
        in.close();
    }
    
    //remove file:
    
    std::remove(test_filename);
}




////////////////////////////////////////////////////////////////////////////////
//  Random methods definition
////////////////////////////////////////////////////////////////////////////////

void seed_random (unsigned int seed)
{
	srand (seed);
}

int random ()
{
	return rand ();
}


int random (int n)
{
	return rand () % (n + 1);
}

int random (int a, int b)
{
	return a + (rand () % (1 + b - a));
}

long int random (long int a, long int b)
{
	return a + (rand () % (1 + b - a));
}

long long int random (long long int a, long long int b)
{
    //const long int a = static_cast<long int>(a_in);
    //const long int b = static_cast<long int>(b_in);
	return a + (rand () % (1 + b - a));
}

unsigned int random (unsigned int n)
{
	return rand () % (n + 1);
}

unsigned int random (unsigned int a, unsigned int b)
{
	return a + (rand () % (1 + b - a));
}

long unsigned int random (long unsigned int a, long unsigned int b)
{
	return a + (rand () % (1 + b - a));
}


long long unsigned int random (long long unsigned int a, long long unsigned int b)
{
    //const long unsigned int a = static_cast<long unsigned int>(a_in);
    //const long unsigned int b = static_cast<long unsigned int>(b_in);
	return a + (rand () % (1 + b - a));
}


double randomReal ()
{
	return static_cast <double> (rand ()) / RAND_MAX;
}

double random (double n)
{
	return randomReal() * n;
}

double random (double a, double b)
{
	return a + random (b - a);
}

float random (float n)
{
	return (static_cast <float> (rand ()) * n) / RAND_MAX;
}

float random (float a, float b)
{
	return a + random (b - a);
}

int random_sign()
{
    return ((rand () %(2)) ? 1 : -1);
}


char randomAtoZ ()
{
	return static_cast <char> (random ('A', 'Z'));
}

char randomatoz ()
{
	return static_cast <char> (random ('a', 'z'));
}

char random1to9 ()
{
	return static_cast <char> (random ('1', '9'));
}

char randomWellFormed()
{
    return static_cast <char> (random (' ', '~'));
}

bool random1in (int n)
{
	return random (n - 1) == 0;
}

bool randomMinN (int m, int n)
{
	return random (n - 1) < m;
}


} // namespace game_dev_utilities


int main(int argc, char*argv[])
{
    game_dev_utilities::run_test();
    
    return 0;
}



