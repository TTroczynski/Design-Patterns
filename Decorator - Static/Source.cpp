#include <string>
#include <iostream>
#include <sstream>
#include <concepts>

using namespace std;

struct Shape
{
	virtual string str() const = 0;
};

struct Circle : Shape
{
	float radius;

	Circle(float radius) : radius(radius) {}

	explicit Circle(const float radius) : radius(radius)
	{

	}

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


//mixing inheritance
//perfect forwarding

template <typename T>
concept IsAShape = std::is_base_of<Shape, T>::value;

template <IsAShape T> struct ColoredShape2 : T
{
	string color;
	ColoredShape2() {}

	template <typename...Args>
	ColoredShape2(const string& color, Args...args) : T(std::forward<Args>(args)...), color(color) {}
};





int main()
{
	
	ColoredShape2<Circle> redCircle;
	

	return 0;
}