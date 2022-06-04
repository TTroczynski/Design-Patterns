
#include <string>
#include <vector>
#include <ostream>
#include <iostream>

class ComponentBuilder
{
	std::string class_name;
	std::vector<std::pair<std::string, std::string>> item_name;

public:
	ComponentBuilder(std::string name) : class_name(name)
	{
	}

	ComponentBuilder& add_Item(std::string item, std::string name)
	{
		item_name.emplace_back(std::make_pair(item, name));
		return *this;
	}

	friend std::ostream& operator << (std::ostream& os, ComponentBuilder& cb) 
	{
		os << cb.class_name << std::endl << "{" << std::endl;
		
		for (const auto& item : cb.item_name)
		{
			os << "  " << item.first << " " << item.second << std::endl;
		}

		os << "};";

		return os;
	}
};

int main(void)
{
	ComponentBuilder cb("class");

	cb.add_Item("string", "test").add_Item("int", "age");

	std::cout << cb;

	return 0;
}