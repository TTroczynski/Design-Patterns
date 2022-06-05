#pragma once


#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <map>
#include <functional>

using namespace std;

class DrinkFactory
{
	map<string, unique_ptr<HotDrinkFactory>> hot_factories;

public:
	DrinkFactory()
	{
		hot_factories["coffee"] = make_unique<CoffeeFactory>();
		hot_factories["tea"] = make_unique<TeaFactory>();

	}

	unique_ptr<HotDrink> make_drink(const string& name)
	{
		auto drink = hot_factories[name]->make();
		drink->prepare(200);
		return drink;
	}
};

//The DrinkFactory below is the Functional Factory
//it stores functions that initialize the objects return them for you using stored functions
//as opposed to an abstract class factory that uses inheritance 

class DrinkWithVolumeFactory
{
	map < string, function<unique_ptr<HotDrink>>();
public:
	DrinkWithVolumeFactory()
	{
		factories["tea"] = [] {
			auto tea = make_unique<Tea>();
			tea->prepare(200);
			return tea;
		};

		factories["coffee"] = [] {
			auto coffee = make_unique<Coffee>();
			coffee->prepare(50);
			return coffee;
		}
	}


	unique_ptr<HotDrink> make_drink(const string& name)
	{
		return factories[name]();
	}
};