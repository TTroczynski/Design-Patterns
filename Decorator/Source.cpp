#include <string>
#include <iostream>
#include <sstream>
#include "di.h"

//dynamic decorator keeps a reference to the decorated object/s
//generally passed as a constructor argument
//creates the opportunity to create functions that perform operations on the object


using namespace std;

struct Shape
{
	virtual string str() const = 0;
};

struct Circle : Shape
{
	float radius;

	Circle(float radius) : radius(radius) {}

	void resize(float factor)
	{
		radius *= factor;
	}

	string str() const override
	{
		ostringstream oss;
		oss << "A circle of radius " << radius;
		return oss.str();
	}
};

struct Square : Shape
{
	float side;

	Square() {}
	Square(float side) : side(side) {}

	string str() const override
	{
		ostringstream oss;
		oss << "A square with side " << side;
		return oss.str();
	}
};

struct ColoredShape : Shape
{
	Shape& shape;
	string color;

	ColoredShape(Shape& shape, const string& color) : shape(shape), color(color)
	{

	}

	string str() const override
	{
		ostringstream oss;
		oss << shape.str() << " has the color " << color;
		return oss.str();
	}
};

struct TransparentShape : Shape
{
	Shape& shape;
	uint8_t transparency;

	TransparentShape(Shape& shape, uint8_t transparency) : shape(shape), transparency(transparency) {}

	string str() const override
	{
		ostringstream oss;
		oss << shape.str() << " has " << static_cast<float>(transparency) / 255.f * 100.f << "% transparency" << endl;
		return oss.str();
	}
};

int main()
{
	Circle circle(5);
	ColoredShape red_circle(circle, "red");
	cout << circle.str() << endl << red_circle.str() << endl;


	//cannot call this member of the because it is not part of the Shape interface
	// so the decorator does not have access to the member
	//red_circle.resize(2);


	TransparentShape my_circle(red_circle, 51);
	cout << my_circle.str();

	

	return 0;
}