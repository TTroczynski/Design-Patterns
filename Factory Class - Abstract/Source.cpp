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
#include "HotDrinkFactory.h"
#include "DrinkFactory.h"

using namespace std;

std::unique_ptr<HotDrink> make_drink(string type)
{
	unique_ptr<HotDrink> drink;
	if (type == "tea")
	{
		drink = make_unique<Tea>();
		drink->prepare(200);
	}
	else 
	{
		drink = make_unique<Coffee>();
		drink->prepare(50);
	}
	return drink;
}

int main(void)
{

	auto d = make_drink("tea");

	DrinkFactory df;
	auto c = df.make_drink("coffee");

	return 0;
}