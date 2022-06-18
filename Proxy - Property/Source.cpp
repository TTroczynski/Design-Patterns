#include <iostream>
#include <string>

using namespace std;



template <typename T> struct Property
{
	T value;
	Property(T value)
	{
		*this = value;
	}

	operator T()
	{
		return value;
	}

	T operator=(T new_value)
	{
		cout << "Assignment!" << endl;
		return value = new_value;
	}
};


struct Creature
{
	Property<int> strength{ 10 };
	Property<int> agility{ 5 };
};


//the property proxy acts as a field that you can use to wrap values so that you can use them as if 
//they were in a struct, but, they are contained within a proxy.
//allows you to define operations on the properties
//allows you to hide the actual values

int main()
{
	Creature c;
	c.strength = 11;
	int x = c.agility;

	cout << c.agility;

	return 0;
}