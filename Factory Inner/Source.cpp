#define _USE_MATH_DEFINES

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>


using namespace std;

enum class PointType
{
	cartesian,
	polar
};

class Point
{
	Point(float x, float y) : x(x), y(y) {} //--------------------- The constructor is private now


	float x, y;

	class PointFactory// ------------------------PointFactory was moved into Point as an inner class
	{
		PointFactory() {}
	public:
		static Point NewCartesian(float x, float y)
		{
			return { x, y };
		}

		static Point NewPolar(float r, float theta)
		{
			return { r * cos(theta), r * sin(theta) };
		}
	};

public:
	friend ostream& operator<< (ostream& os, Point& pt)
	{
		os << "x: " << pt.x << ", y: " << pt.y << std::endl;

		return os;
	}

	//Moved the point factory class into the Point class as an inner class
	//Since the constructor of Point is private, this makes it more obvious that the implementor needs to use the PointFactory inner class to initialize
	//a Point object.
	//When they were seperate, it would not be immediately obvious that the PointFactory was meant to be used to initialize a point
	
	static PointFactory Factory;//-------------------static member of type PointFactory that is exposed as public. Through this you make new Point types
};



int main(void)
{
	//auto p = Point::PointFactory::NewPolar(5, M_PI_4);
	auto p = Point::Factory.NewPolar(5, M_PI_4);


	std::cout << p;

	return 0;
}