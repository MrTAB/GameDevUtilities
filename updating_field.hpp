/*
*
*	updating_field.hpp
*   
*   Updating fields are values which can be externally updated with respect to
*   some given update method and parameters. This update happens periodically,
*   changing the value across time in a way that is interdependant of the entity
*   making use of the field.
*
*   Updating fields can be used for animating fields for enemies or game objects
*   or for the coordinates of moving objects such as bullets of particles for
*   describing their movement in a way that is aesthetically pleasing with
*   little effort. By abstracting and generalising the mechanical changes,
*   particles and the like can focus their codebase on their creation and
*   interaction.
*
*   Updating fields were created as a solution for particle system movement,
*   where unique particle types may wish to move independently but without
*   either a) using polymorphism as the particles were to be contigiously
*   stored or b) cluttering the particles with conditional behaviour.
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



#ifndef GAME_DEV_UTILITIES_UPDATING_FIELD_HPP
#define GAME_DEV_UTILITIES_UPDATING_FIELD_HPP
#include<types/const.hpp>
#include<cmath>
namespace game_dev_utilities
{
    
class updating_field_t
{
	public:
	
		enum update_method_t
		{
			NOTHING,
			ADD,
			ADD_TO_ADD,
			ADD_TO_ADD_BA,
			MULTIPLY_ADD,
			MULTIPLY_ADD_BA,
			MULTIPLY,
			MULTIPLY_BASE,
			MULTIPLY_BASE_BA,
			ATTENUATE,
			ATTENUATE_BA,
			ATTENUATE_LINEARLY,
			ATTENUATE_LINEARLY_BA
		};
		
	private:
			
		float value;
		float param_A;
		float param_B;	
		update_method_t update_method;
	
	public:
	
		explicit updating_field_t(cfloat value_in = 0):
			value(value_in),
			param_A(0),
			param_B(0),
			update_method(NOTHING)
		{
			// do nothing //
		}
		
		void set_value(cfloat value_in)
		{
			value = value_in;
		}	
		
		void set_update_method(const update_method_t update_method_in, cfloat param_A_in, cfloat param_B_in = 0)
		{
			update_method = update_method_in;
			param_A = param_A_in;
			param_B = param_B_in;
		}

		
		operator float() const
		{
			return value;
		}
		
		float operator = (cfloat value_in)
		{
		    return value = value_in;
		}
		
		float operator += (cfloat value_in)
		{
		    return value += value_in;
		}
		
		float operator -= (cfloat value_in)
		{
		    return value -= value_in;
		}
		
		void add(cfloat inc)
		{
		    set_update_method(ADD,inc);
		}
		void add_by_A_compound_add_by_B(cfloat A, cfloat B)
		{
		    set_update_method(ADD_TO_ADD,A,B);
		}
		void inc_by_A_compound_multiplied_by_B(cfloat A, cfloat B)
		{
		    set_update_method(MULTIPLY_ADD,A,B);
		}
		void multiply(cfloat A)
		{
		    set_update_method(MULTIPLY,A);
		}
		void multiply_base(cfloat base_value, cfloat multiplier)
		{
		    set_update_method(MULTIPLY_BASE, multiplier, base_value);
		}
		void attenuate(cfloat target, cfloat close_in_ratio)
		{
		    set_update_method(ATTENUATE,target,close_in_ratio);
		}
		void attenuate_linearly(cfloat target, cfloat close_in_value)
		{
		    set_update_method(ATTENUATE_LINEARLY,target,close_in_value);
		}
		
		void update(cuint time = 0)
		{
			switch(update_method)
			{
				case ADD:
				{
					value += param_A + param_B;
					break;
				}
				case ADD_TO_ADD:
				{
					value += param_A;
					param_A += param_B;
					break;
				}
				case ADD_TO_ADD_BA:
				{
					value += param_B;
					param_B += param_A;
					break;
				}
				case MULTIPLY_ADD:
				{
					value += param_A;
					param_A *= param_B;
					break;
				}
				case MULTIPLY_ADD_BA:
				{
					value += param_B;
					param_B *= param_A;
					break;
				}
				case MULTIPLY:
				{
					value *= param_A;
					break;
				}
				case MULTIPLY_BASE:
				{
					value = param_B + (value-param_B) * param_A;
					break;
				}
				case MULTIPLY_BASE_BA:
				{
					value = param_A + (value-param_A) * param_B;
					break;
				}
                case ATTENUATE:
                {
                    value += (param_A-value)*param_B;
                    break;
                }
                case ATTENUATE_BA:
                {
                    value += (param_B-value)*param_A;
                    break;
                }
                case ATTENUATE_LINEARLY:
                {
                    value += param_B;
                    if(std::abs((param_A-value)) < param_B)
                    {
                        value = param_B;
                    }
                    break;
                }
                case ATTENUATE_LINEARLY_BA:
                {
                    value += param_A;
                    if(std::abs((param_B-value)) < param_A)
                    {
                        value = param_A;
                    }
                    break;
                }
				case NOTHING:
				default:
				{
					break;
				}
			}
		}
	
};




} // namespace super_pixel_boy
#endif // GAME_DEV_UTILITIES_UPDATING_FIELD_HPP


