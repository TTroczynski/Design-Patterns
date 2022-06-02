#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

using namespace std;

enum class Relationship
{
	PARENT,
	CHILD,
	SIBLING
};

struct Person
{
	string name;
};

struct Relationships //-------------------------------------------------Relationships is considered to be a low-level module
{																	//	low-level construct....because it directly deals with the 'thing'
	vector<tuple<Person, Relationship, Person>> relations;

	void add_parent_and_child(const Person& parent, const Person& child)
	{
		relations.push_back({ parent, Relationship::PARENT, child });
		relations.push_back({ child, Relationship::CHILD, parent });
	}

};

struct Research // High level
{
	//breaks because this will have a dependency on a low level module
	Research(Relationships& relationships)
	{
		auto& relations = relationships.relations;

		for (auto&& [first, rel, second] : relations)
		{
			if (first.name == "John" && rel == Relationship::PARENT)
			{
				cout << "John has a child called " second.name << endl;
			}
		}
	}
};

int main()
{
	Person parent{ "john" };
	Person child1{ "Chris" }, child2{ "Matt" };

	Relationships relationships;
	relationships.add_parent_and_child(parent, child1);
	relationships.add_parent_and_child(parent, child2);

	Research _(relationships);
	return 0;
}