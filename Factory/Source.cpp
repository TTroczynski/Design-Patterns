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

struct Point
{
	

	//Point(float x, float y) : x(x), y(y) {} //By creating the enum class PointType, we can create different constructors by including the enum value as a specifier
	
	/*
	Point(float rho, float theta) //isnt allowed because the constructor has the same parameter types. Its the same constructor as the one above. Cant have more than one.
	*/

	Point(float x, float y) : x(x), y(y) {}


public:
	float x, y;

	static Point NewCartesian(float x, float y)
	{
		return { x, y };
	}

	static Point NewPolar(float r, float theta)
	{
		return { r * cos(theta), r * sin(theta) };
	}

	friend ostream& operator<< (ostream& os, Point& pt)
	{
		os << "x: " << pt.x << ", y: " << pt.y << std::endl;

		return os;
	}
	
};

int main(void)
{
	auto p = Point::NewPolar(5, M_PI_4);

	std::cout << p;

	return 0;
}