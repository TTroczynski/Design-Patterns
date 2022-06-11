#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>
#include <array>

using namespace std;

//**********************************************************************************
// 
// This class is depends on the private variables never changing
// if new ones are added, functions like sum and average would have to be re written
// to include the new variable.
// 
// *********************************************************************************
// 
// 
//class Creature
//{
//	int strength, agility, intelligence;
//
//public:
//	
//	int get_strength() const
//	{
//		return strength;
//	}
//	void set_strength(int strength)
//	{
//		this->strength = strength;
//	}
//	int get_agility() const
//	{
//		return agility;
//	}
//	void set_agility(int agility)
//	{
//		this->agility = agility;
//	}
//	int get_intelligence() const
//	{
//		return intelligence;
//	}
//	void set_intelligence(int intelligence)
//	{
//		this->intelligence = intelligence;
//	}
//
//	double sum() const
//	{
//		return strength + agility + intelligence;
//	}
//
//	double average() const
//	{
//		return sum() / 3.0;
//	}
//
//	int max() const 
//	{
//		return ::max(::max(strength, agility), intelligence);
//	}
//
//};



class Creature
{
	enum Abilities { str, agl, intl, count};
	array<int, count> abilities;

public:
	int get_strength() const 
	{ 
		return abilities[str]; 
	}
	void set_strength(int value) 
	{ 
		abilities[str] = value; 
	}
	int get_agility() const 
	{ 
		return abilities[agl]; 
	}
	void set_agility(int value) 
	{ 
		abilities[agl] = value; 
	}
	int get_intelligence() const 
	{ 
		return abilities[intl]; 
	}
	void set_intelligence(int value) 
	{ 
		abilities[intl] = value; 
	}

	int sum() const
	{
		int sum = 0;
		for (int stat : abilities)
		{
			sum += stat;
		}

		return sum;
	}

	double average() const
	{
		return sum() / abilities.size();
	}

	int max() const
	{
		int max = 0;

		for (int i = 0; i < count - 1; i++) {

			for (int j = i; j < count; j++)
			{
				if (abilities[j] > abilities[max])
				{
					max = j;
				}
			}
		}

		return max;
	}


};


int main(int ac, char* av[])
{
	Creature orc;
	orc.set_strength(9);
	orc.set_agility(9);
	orc.set_intelligence(20);

	cout << "The orc has an average stat of " << orc.average();
	cout << "The highest stat is " << orc.max() << endl;

	return 0;
}