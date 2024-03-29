#pragma once
#include <string>
#include <iostream>
#include <memory>

struct HotDrink
{
	virtual ~HotDrink() = default;
	virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{
	void prepare(int volume) override {
		std::cout << "Take a tea bag, boil water, pour " << volume << "ml , add some lemon" << std::endl;
	}
};

struct Coffee : HotDrink
{
	void prepare(int volume) override {
		std::cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!" << std::endl;
	}
};