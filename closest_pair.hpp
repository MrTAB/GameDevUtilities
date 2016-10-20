/*
*
*	closest_pair.hpp
*
*   This is a soluton to finding an approximation of the closest pair of points
*   from a list of stationary points. This method takes a few shortcuts with
*   the intention of saving time at the expense of accuracy, where a certain
*   amount of priority will be given to y close points than x close points
*   (perfect for a 2d sidescrolling environment). In addition, the points are
*   expected to be known ahead of time, such that they can be kept in two
*   sorted lists - one sorted by x coordinate, and the other by y coordinate.
*   
*   The primary method to call for this purpose is:
*    
*     distanced_points_t find_closest_using_divide(point_vector_t&x_points,
*                                                  point_vector_t&y_points);
*                                                
*   This will return an instance of distanced_points_t which has an is_valid()
*   method to check that the operation was able to find such points. The points
*   can then be accessed via the field points, which is std::pair of point_t 
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





#ifndef GAME_DEV_UTILITIES_CLOSEST_PAIR_HPP
#define GAME_DEV_UTILITIES_CLOSEST_PAIR_HPP
#include<vector>
#include<cmath>
#include<limits>
#include<algorithm>
#include<cassert>

///OPTION:
// option - for external libraries using point_t in their own containers: allows
// int quantized comparison. Does not affect this library internally.
#define CLOSEST_PAIR_POINTS_COMPARE_AS_INTS 

#ifdef CLOSEST_PAIR_POINTS_COMPARE_AS_INTS
#include"floats.hpp"
#endif
namespace game_dev_utilities
{
namespace closest_pair
{
namespace floats = super_pixel_boy::floats;


//optimize - replace with front end that leaves sqrt until the end.
// needs to be updated through brute force etc as well.

struct point_t
{
    float x;
    float y;
    
    float distance_to(const point_t other)const
    {
        return std::sqrt((other.x - x)*(other.x - x) + (other.y - y)*(other.y - y));
    }
    
    float squared_distance_to(const point_t other)const
    {
        return std::sqrt((other.x - x)*(other.x - x) + (other.y - y)*(other.y - y));
    }
    
    static bool x_less(const point_t a, const point_t b)
    {
        return a.x < b.y;
    }

    static bool y_less(const point_t a, const point_t b)
    {
        return a.y < b.y;
    }

    bool operator==(point_t other)const
    {
        #ifdef CLOSEST_PAIR_POINTS_COMPARE_AS_INTS
        return static_cast<int>(x) == static_cast<int>(other.x)
            && static_cast<int>(y) == static_cast<int>(other.y);
        #else
        return floats::compare(x,other.x) && floats::compare(y,other.y);
        #endif
    }
    
    
    static point_t min()
    {
        point_t m = {std::numeric_limits<float>::min(),std::numeric_limits<float>::min()};
        return m;
    };
    
	static point_t max()
	{
	    point_t m = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
	    return m;
	}
	
	static point_t zero()
	{
	    point_t z = {0.f, 0.f};
	    return z;
	}
        
};

static point_t make_point(const float x, const float y)
{
    point_t p = {x, y};
    return p;
}

typedef std::vector<point_t>  point_vector_t;

class sub_vector_t
{
        point_vector_t::iterator _begin;
        point_vector_t::iterator _end;
	 
    public:
    
    sub_vector_t(point_vector_t::iterator _begin_in,
                 point_vector_t::iterator _end_in):
        _begin(_begin_in), _end(_end_in)
    {       
        assert(_begin < _end);
    }
    
	const point_vector_t::iterator begin() const { return _begin; }
	const point_vector_t::iterator end() const { return _end; }
	
	point_vector_t::iterator begin() { return _begin; }
	point_vector_t::iterator end() { return _end; }
	
	const point_t front() const { return *_begin; }
	const point_t back() const { return *(_end-1); }
	
	point_t front() { return *_begin; }
	point_t back() { return *(_end-1); }
	
	size_t size()const
	{
	    return std::distance(_begin,_end);
	}
};


typedef std::pair<point_t,point_t> point_pair_t;

struct distanced_points_t
{
	float distance;
	point_pair_t points;
	
	distanced_points_t(const float distance_in,
                    const point_pair_t points_in):
		distance(distance_in),points(points_in)
	{
	    // do nothing //
	}
	
	distanced_points_t(const float distance_in,
                    const point_t first,
                    const point_t second):
            distance(distance_in),
            points(std::make_pair(first,second))
	{
	    // do nothing //
	}
	
	distanced_points_t min(distanced_points_t other)
	{
		if(other.distance < distance)
		{
			return other;
		}
		return *this;
	}
	
	void set(const  float distance_in,
		const point_pair_t points_in)
    {
        distance = distance_in;
        points = points_in;
    }
    
	void set(const float distance_in,
		const point_t first,
		const point_t second)
    {
        distance = distance_in;
        points.first = first;
        points.second = second;
    }
    
    bool is_valid()const
    {
        return !std::isnan(distance)
            && !(std::numeric_limits<float>::has_infinity
                && std::numeric_limits<float>::infinity() == distance);
    }
    
    static distanced_points_t infinity()
    {
        point_t min = point_t::min();
	    point_t max = point_t::max();
	    return distanced_points_t(std::numeric_limits<float>::infinity(),min, max);
    }
};



struct x_distance_to_a_less_than_b_t
{
	float a;
	float b;	
	explicit x_distance_to_a_less_than_b_t(const float a_in,
					const float b_in):
					a(a_in),
					b(b_in)
	{
	}
	bool operator()(const point_t p)const
	{
		return std::abs(a - p.x) < b;
	}
};
	
	


	
static distanced_points_t find_closest_squared_using_brute(point_vector_t& points)
{
	if(points.size() < 2)
	{	    
		return  distanced_points_t::infinity();
	}
	else
	{
		distanced_points_t closest(std::abs(points[1].squared_distance_to(points[0])),
								std::make_pair(points[0],
										 points[1]));		
		
		for(auto i = points.begin(); i != points.end() - 1; ++i)
		{
			for(auto j = i+1; j != points.end(); ++j)
			{
				if(std::abs(i->squared_distance_to(*j)) < closest.distance)
				{
					closest.set(std::abs(i->squared_distance_to(*j)), *i, *j);
				}
			}
		}
		return closest;
	}
}

inline distanced_points_t find_closest_using_brute(point_vector_t& points)
{
    distanced_points_t result = find_closest_squared_using_brute(points);
    if(result.is_valid())
    {
        result.distance = std::sqrt(result.distance);
    }
    return result;
}


static distanced_points_t find_closest_squared_using_divide(sub_vector_t x_points,
			point_vector_t&y_points) //sorted by y
{			
	size_t count = x_points.size();
	
	if(count < 3)
	{
		return find_closest_squared_using_brute(y_points);
	}
	else
	{
		sub_vector_t x_left(x_points.begin(), x_points.begin() + std::ceil(count/2.f));
		sub_vector_t x_right(x_left.end(), x_points.end());
		const float middle_x = x_left.back().x;

		point_vector_t y_left; 
		point_vector_t y_right;
					
        for(auto itr = y_points.begin();itr!=y_points.end();++itr)	
        {
            if(itr->x > middle_x)
            {
                y_right.push_back(*itr);
            }
            else
            {
                y_left.push_back(*itr);
            }
        }
		
		auto left = find_closest_squared_using_divide(x_left, y_left);
		auto right = find_closest_squared_using_divide(x_right, y_right);
		auto min = right.min(left);
		
		point_vector_t y_search;
		std::copy_if(y_points.begin(),
					y_points.end(),
					std::back_inserter(y_search),
					x_distance_to_a_less_than_b_t(middle_x, min.distance));
		
		auto closest = min;
		
		if(!y_search.empty())
		{
            for(auto i = y_search.begin(); i != y_search.end()-1; ++i)
            {
                for(auto k = i + 1;
                    k != y_search.end() && (k->y - i->y < min.distance);
                    ++k)
                {
                    if(std::abs(k->squared_distance_to(*i)) < closest.distance)
                    {
                        closest.distance = std::abs(k->squared_distance_to(*i));
                        closest.points = std::make_pair(*k, *i);
                    }
                }
            }
		}
		
		return closest;
		
	}
}

inline distanced_points_t find_closest_using_divide(sub_vector_t x_points,
                                                    point_vector_t&y_points)
{
    distanced_points_t result = find_closest_squared_using_divide(x_points,y_points);
    
    if(result.is_valid())
    {
        result.distance = std::sqrt(result.distance);
    }
    
    return result;
}

inline distanced_points_t find_closest_using_divide(point_vector_t&x_points,
			point_vector_t&y_points)
{
    sub_vector_t x_points_sub(x_points.begin(), x_points.end());
    
    return find_closest_using_divide(x_points_sub,y_points);
}

}
} // namespace closest_pair
#endif // GAME_DEV_UTILITIES_CLOSEST_PAIR_HPP


