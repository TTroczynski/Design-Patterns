#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>
#include <map>

#include "di.h"
#include "headers.h"
#include <boost/lexical_cast.hpp>


using namespace boost;
using namespace std;

//dependency injection container allows you to create different object with different lifetimes

struct IFoo
{
	virtual string name() = 0;

};

struct Foo : IFoo
{
	static int id;

	Foo()
	{
		id++;
	}

	string name() override {
		return "Foo "s + lexical_cast<string>(id);
	}
};

int Foo::id = 0;

struct Bar
{
	std::shared_ptr<IFoo> foo;
};

int main()
{
	//using the dependency injection framework, you can configure a single component to behave as a singleton
	//instead of creating your own.
	//
	auto injector = di::make_injector(
		di::bind<IFoo>().to<Foo>().in(di::singleton)
	);

	auto bar1 = injector.create<std::shared_ptr<Bar>>();
	auto bar2 = injector.create<std::shared_ptr<Bar>>();

	cout << bar1->foo->name() << endl;
	cout << bar2->foo->name() << endl;

	cout << boolalpha << (bar1->foo.get() == bar2->foo.get()) << endl;
}