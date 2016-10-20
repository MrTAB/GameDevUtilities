/*
*
*	angles.cpp
*
*   A set of utility methods for working with angles during
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


#include"angles.hpp"
#include"normal_methods.hpp"
namespace game_dev_utilities
{
namespace angles
{



//accepts radians in any range
//returns in range [0,2*pi)
float clipped_to_right_angle(float radians)
{
    using namespace normal;
    using floats::pi;    
    return get_quadrant(angles::normalised_radians(radians)) * floats::pi/2.f;
}

/*
    :TEST
    using floats::pi;
    DOUT("\clipped_to_right_angle TEST:");
    DOUT("\n0\t"<<float_to_string_in_radians(clipped_to_right_angle(0)));
    DOUT("\n0\t"<<float_to_string_in_radians(clipped_to_right_angle(pi/6.f)));
    DOUT("\npi/2\t"<<float_to_string_in_radians(clipped_to_right_angle(2*pi/6.f)));
    DOUT("\npi/2\t"<<float_to_string_in_radians(clipped_to_right_angle(pi/2.f)));
    DOUT("\npi/2\t"<<float_to_string_in_radians(clipped_to_right_angle(4*pi/6.f)));
    DOUT("\npi\t"<<float_to_string_in_radians(clipped_to_right_angle(5*pi/6.f)));
    DOUT("\npi\t"<<float_to_string_in_radians(clipped_to_right_angle(pi)));
    DOUT("\n0\t"<<float_to_string_in_radians(clipped_to_right_angle(-pi/6.f)));
    DOUT("\n-pi/2\t"<<float_to_string_in_radians(clipped_to_right_angle(-2*pi/6.f)));
    DOUT("\n-pi/2\t"<<float_to_string_in_radians(clipped_to_right_angle(-pi/2.f)));
    DOUT("\n-pi/2\t"<<float_to_string_in_radians(clipped_to_right_angle(-4*pi/6.f)));
    DOUT("\n-pi\t"<<float_to_string_in_radians(clipped_to_right_angle(-5*pi/6.f)));
    DOUT("\n-pi\t"<<float_to_string_in_radians(clipped_to_right_angle(-pi)));
    
    */


#ifdef ANGLES_TESTS


std::string float_to_string_in_radians(const float f)
{
    const float r = f/floats::pi;
    std::stringstream ss;
    
    /*if(floats::compare(r,1.f))
    {
        ss << "pi";
    }
    else if (floats::compare(r,-1.f))
    {
        ss<< "-pi";
    }
    else if (floats::compare(r,0.5f))
    {
        ss<< "pi/2";
    }
    else if (floats::compare(r,-0.5f))
    {
        ss<< "-pi/2";
    }
    else if (floats::is_zero(r))
    {
        ss<< "0";
    }
    else*/
    {
        ss << r << "pi";
    }
    
    return ss.str();

}

void test_float_to_string_in_radians()
{
    std::cout<<"\npi "<<float_to_string_in_radians(pi);
    std::cout<<"\n-pi "<<float_to_string_in_radians(-pi);
    std::cout<<"\npi/2 "<<float_to_string_in_radians(pi/2);
    std::cout<<"\n-pi/2 "<<float_to_string_in_radians(-pi/2);
    std::cout<<"\n2pi "<<float_to_string_in_radians(2*pi);
    std::cout<<"\n-2pi "<<float_to_string_in_radians(-2*pi);
    std::cout<<"\n0.75pi "<<float_to_string_in_radians(0.75f*pi);
    std::cout<<"\n-0.75pi "<<float_to_string_in_radians(-0.75f*pi);
    std::cout<<"\n0 "<<float_to_string_in_radians(0);
    std::cout<<"\n-0 "<<float_to_string_in_radians(-0);
}

void test_normalised_radians()
{
    using floats::pi;
    
    assert(!(pi > pi));
    
    std::cout <<"\n0\t" << float_to_string_in_radians(normalised_radians(0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(normalised_radians(pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(normalised_radians(pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(normalised_radians(pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(normalised_radians(pi+0));
    std::cout <<"\n1.25pi\t" << float_to_string_in_radians(normalised_radians(pi+pi/4));
    std::cout <<"\n1.5pi\t" << float_to_string_in_radians(normalised_radians(pi+pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(normalised_radians(pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(normalised_radians(2*pi+0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(normalised_radians(2*pi+pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(normalised_radians(2*pi+pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(normalised_radians(2*pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(normalised_radians(3*pi+0));
    std::cout <<"\n1.25pi\t" << float_to_string_in_radians(normalised_radians(3*pi+pi/4));
    std::cout <<"\n1.5\t" << float_to_string_in_radians(normalised_radians(3*pi+pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(normalised_radians(3*pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(normalised_radians(4*pi+0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(normalised_radians(4*pi+pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(normalised_radians(4*pi+pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(normalised_radians(4*pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n-0\t" << float_to_string_in_radians(normalised_radians(-0));
    std::cout <<"\n1.75pi\t" << float_to_string_in_radians(normalised_radians(-pi/4));
    std::cout <<"\n1.5pi\t" << float_to_string_in_radians(normalised_radians(-pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(normalised_radians(-pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(normalised_radians(-pi-0));
    std::cout <<"\n0.75pi\t" << float_to_string_in_radians(normalised_radians(-pi-pi/4));
    std::cout <<"\n0.5pi\t" << float_to_string_in_radians(normalised_radians(-pi-pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(normalised_radians(-pi-pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(normalised_radians(-2*pi-0));
    std::cout <<"\n1.75*pi\t" << float_to_string_in_radians(normalised_radians(-2*pi-pi/4));
    std::cout <<"\n1.5pi\t" << float_to_string_in_radians(normalised_radians(-2*pi-pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(normalised_radians(-2*pi-pi));
    
    /*
    std::cout <<"" << normalised_radians(float_to_string_in_radians());
    std::cout <<"" << normalised_radians(float_to_string_in_radians());
    std::cout <<"" << normalised_radians(float_to_string_in_radians());
    std::cout <<"" << normalised_radians(float_to_string_in_radians());
    std::cout <<"" << normalised_radians(float_to_string_in_radians());
    */
    
}

void test_angle_to_pirange()
{
    //using vector::angle_to_pirange;
    using floats::pi;
    
    assert(!(pi > pi));
    
    std::cout <<"\n0\t" << float_to_string_in_radians(angle_to_pirange(0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(angle_to_pirange(pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(angle_to_pirange(pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(angle_to_pirange(pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(angle_to_pirange(pi+0));
    std::cout <<"\n-0.75pi\t" << float_to_string_in_radians(angle_to_pirange(pi+pi/4));
    std::cout <<"\n-pi/2\t" << float_to_string_in_radians(angle_to_pirange(pi+pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(angle_to_pirange(pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(angle_to_pirange(2*pi+0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(angle_to_pirange(2*pi+pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(angle_to_pirange(2*pi+pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(angle_to_pirange(2*pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n-0\t" << float_to_string_in_radians(angle_to_pirange(-0));
    std::cout <<"\n-0.25*pi\t" << float_to_string_in_radians(angle_to_pirange(-pi/4));
    std::cout <<"\n-pi/2\t" << float_to_string_in_radians(angle_to_pirange(-pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(angle_to_pirange(-pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(angle_to_pirange(-pi-0));
    std::cout <<"\n0.75pi\t" << float_to_string_in_radians(angle_to_pirange(-pi-pi/4));
    std::cout <<"\n0.5pi\t" << float_to_string_in_radians(angle_to_pirange(-pi-pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(angle_to_pirange(-pi-pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(angle_to_pirange(-2*pi-0));
    std::cout <<"\n-0.25*pi\t" << float_to_string_in_radians(angle_to_pirange(-2*pi-pi/4));
    std::cout <<"\n-pi/2\t" << float_to_string_in_radians(angle_to_pirange(-2*pi-pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(angle_to_pirange(-2*pi-pi));
    
    /*
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    */
    
}



inline void test_clipped_radians()
{
    using floats::pi;
    
    assert(!(pi > pi));
    
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_radians(0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(clipped_radians(pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(clipped_radians(pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_radians(pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_radians(pi+0));
    std::cout <<"\n1.25pi\t" << float_to_string_in_radians(clipped_radians(pi+pi/4));
    std::cout <<"\n1.5pi\t" << float_to_string_in_radians(clipped_radians(pi+pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_radians(pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_radians(2*pi+0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(clipped_radians(2*pi+pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(clipped_radians(2*pi+pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_radians(2*pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_radians(3*pi+0));
    std::cout <<"\n1.25pi\t" << float_to_string_in_radians(clipped_radians(3*pi+pi/4));
    std::cout <<"\n1.5\t" << float_to_string_in_radians(clipped_radians(3*pi+pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_radians(3*pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_radians(4*pi+0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(clipped_radians(4*pi+pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(clipped_radians(4*pi+pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_radians(4*pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n-0\t" << float_to_string_in_radians(clipped_radians(-0));
    std::cout <<"\n1.75pi\t" << float_to_string_in_radians(clipped_radians(-pi/4));
    std::cout <<"\n1.5pi\t" << float_to_string_in_radians(clipped_radians(-pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_radians(-pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_radians(-pi-0));
    std::cout <<"\n0.75pi\t" << float_to_string_in_radians(clipped_radians(-pi-pi/4));
    std::cout <<"\n0.5pi\t" << float_to_string_in_radians(clipped_radians(-pi-pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_radians(-pi-pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_radians(-2*pi-0));
    std::cout <<"\n1.75*pi\t" << float_to_string_in_radians(clipped_radians(-2*pi-pi/4));
    std::cout <<"\n1.5pi\t" << float_to_string_in_radians(clipped_radians(-2*pi-pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_radians(-2*pi-pi));
}


void test_clipped_to_pirange()
{
    //using vector::angle_to_pirange;
    using floats::pi;
    
    assert(!(pi > pi));
    
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_to_pirange(0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(clipped_to_pirange(pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(clipped_to_pirange(pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_to_pirange(pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_to_pirange(pi+0));
    std::cout <<"\n-0.75pi\t" << float_to_string_in_radians(clipped_to_pirange(pi+pi/4));
    std::cout <<"\n-pi/2\t" << float_to_string_in_radians(clipped_to_pirange(pi+pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_to_pirange(pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_to_pirange(2*pi+0));
    std::cout <<"\n0.25*pi\t" << float_to_string_in_radians(clipped_to_pirange(2*pi+pi/4));
    std::cout <<"\npi/2\t" << float_to_string_in_radians(clipped_to_pirange(2*pi+pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_to_pirange(2*pi+pi));
    std::cout <<"\n";
    
    std::cout <<"\n-0\t" << float_to_string_in_radians(clipped_to_pirange(-0));
    std::cout <<"\n-0.25*pi\t" << float_to_string_in_radians(clipped_to_pirange(-pi/4));
    std::cout <<"\n-pi/2\t" << float_to_string_in_radians(clipped_to_pirange(-pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_to_pirange(-pi));
    std::cout <<"\n";
    
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_to_pirange(-pi-0));
    std::cout <<"\n0.75pi\t" << float_to_string_in_radians(clipped_to_pirange(-pi-pi/4));
    std::cout <<"\n0.5pi\t" << float_to_string_in_radians(clipped_to_pirange(-pi-pi/2));
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_to_pirange(-pi-pi));
    std::cout <<"\n";
    
    std::cout <<"\n0\t" << float_to_string_in_radians(clipped_to_pirange(-2*pi-0));
    std::cout <<"\n-0.25*pi\t" << float_to_string_in_radians(clipped_to_pirange(-2*pi-pi/4));
    std::cout <<"\n-pi/2\t" << float_to_string_in_radians(clipped_to_pirange(-2*pi-pi/2));
    std::cout <<"\npi\t" << float_to_string_in_radians(clipped_to_pirange(-2*pi-pi));
    
    /*
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    std::cout <<"" << angle_to_pirange(float_to_string_in_radians());
    */
    
}




#endif

}
}

