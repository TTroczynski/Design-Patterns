#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct GraphicObject
{
	virtual void draw() = 0;
};

struct Circle : GraphicObject
{
	void draw() override
	{
		cout << "Circle" << endl;
	}
};

struct Group : GraphicObject
{
	string name;
	vector<GraphicObject*> objects;

	Group(const string& name) : name(name) {}

	void draw() override
	{
		cout << "Group " << name.c_str() << " contains: " << endl;
		for (auto&& o : objects)
		{
			o->draw();
		}
	}
};

int main()
{
	//allows us to treat individual objects and aggregate objects uniformly
	//sigular object and groups get treated the same way
	//objects use other objects fields/properties/members through inheritance and composition

	//composition lets you make compount objects

	//the GraphicObject interface allows us to use singular objects and group objects the same way

	Group root("root");
	Circle c1, c2;
	root.objects.push_back(&c1);

	Group subgroup("sub");
	subgroup.objects.push_back(&c2);

	root.objects.push_back(&subgroup);

	root.draw();


	return 0;
}