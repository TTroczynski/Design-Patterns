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

struct RelationshipBrowser
{
	virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser //-------------------------------------------------Relationships is considered to be a low-level module
{																	//	low-level construct....because it directly deals with the 'thing'
	vector<tuple<Person, Relationship, Person>> relations;
	//IF this vector of relationships ever changes, or changes inheritance to 'Private'
	//then all the higher level code 'Research' will cease working
	//because it is written in a way that depend on the way that this lower level code is written

	void add_parent_and_child(const Person& parent, const Person& child)
	{
		relations.push_back({ parent, Relationship::PARENT, child });
		relations.push_back({ child, Relationship::CHILD, parent });
	}

	vector<Person> find_all_children_of(const string& name) override {
		vector<Person> result;
		for (auto& entry : relations) {
			Person first, second;
			Relationship rel;
			tie(first, rel, second) = entry;

			if (first.name == name && rel == Relationship::PARENT) {
				result.push_back(second);
			}
		}
		return result;
	}

};

struct Research // High level
{
	//breaks because this will have a dependency on a low level module
	/*
	Research(Relationships& relationships)
	{
		auto& relations = relationships.relations;

		for (auto&& entry : relations)
		{
			Person first, second;
			Relationship rel;
			tie(first, rel, second) = entry;

			if (first.name == "John" && rel == Relationship::PARENT)
			{
				cout << "John has a child called " << second.name << endl;
			}
		}
	}
	*/



	//By implementing an interface called "RelationshipBrowser" we have defined an interface through which
	//the programmer can access the relationships stored in the Relationships vector of tuples

	//so no matter what changes behind the API, the functionality is not affected on the implementation side

	//the implementation no longer does any work using any low level module.
	//instead it takes an interface through which it will call the functions implemented by the objects that 
	//implement the interface.
	Research(RelationshipBrowser& browser) {
		for (auto& child : browser.find_all_children_of("John")) {
			cout << "John has a child called " << child.name << endl;
		}
	}
	
};

int main()
{
	Person parent{ "John" };
	Person child1{ "Chris" }, child2{ "Matt" };

	Relationships relationships;
	relationships.add_parent_and_child(parent, child1);
	relationships.add_parent_and_child(parent, child2);

	Research _(relationships);
	return 0;
}