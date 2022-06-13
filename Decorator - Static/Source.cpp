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

	/*explicit Circle(const float radius) : radius(radius)
	{

	}*/

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

	string str() const override
	{
		ostringstream oss;
		oss << T::str() << " has the color " << color;
		return oss.str();
	}
};

template <IsAShape T> struct TransparentShape2 : T
{
	uint8_t transparency;

	template<typename...Args>
	TransparentShape2(const uint8_t transparency, Args ...args) : T(std::forward<Args>(args)...), transparency(transparency) {}

	string str() const override
	{
		ostringstream oss;
		oss << T::str() << " has " << static_cast<float>(transparency) / 255.f * 100.f << "% transparency" << endl;
		return oss.str();
	}
};





int main()
{
	//you cant resize the circle that is used to create an instance of ColoredShape through ColoredShape
	Circle aCircle(5);
	ColoredShape coloredShape(aCircle, "red");
	cout << coloredShape.str() << endl;

	//using ColoredShape2 you can access members of Circle
	ColoredShape2<Circle> greenCircle("green", 5);
	//because ColoredShape2 is a generic class, that inherits from the specified type
	// as long as it is one that is a 'Shape'
	//
	//the alternative is that you can use decorators but the objects will not have access to the 
	//decorated object's members
	//it will have access to any inherited methods 

	cout << greenCircle.str() << endl;
	

	TransparentShape2<ColoredShape2<Square>> bis(0, "blue", 10);
	bis.color = "light blue";
	bis.side = 21;
	cout << bis.str() << endl;

	//bis is a TransparentShape2, which inherits from ColoredShape2, which inherits from Square.
	//the constructor argument forwarding lets each constructor assign the value of the argument that
	//corrensponds to it.
	//This allows you to give member access to the object while also decorating 

	return 0;
}