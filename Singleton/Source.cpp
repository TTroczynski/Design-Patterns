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
#include <boost/lexical_cast.hpp>

using namespace boost;

using namespace std;


class Database
{
public:
	virtual int get_population(const string& name) = 0;
};

class SingletonDatabase : public Database
{
	SingletonDatabase()
	{
		cout << "Initializing database" << endl;

		ifstream ifs("capitals.txt");

		string s, s2;

		while (getline(ifs, s))
		{
			getline(ifs, s2);
			int pop = lexical_cast<int>(s2);
			capitals[s] = pop;
		}
	}

	map<string, int> capitals;
public:
	//prevent any copying of instances of this class....
	SingletonDatabase(SingletonDatabase const&) = delete;
	void operator=(SingletonDatabase const&) = delete;

	static SingletonDatabase& get()
	{
		//static instance in a class that prevents copying - single universal instance of a thing
		//makes it so that no matter how many times you call get(), you always get the same instance back
		static SingletonDatabase db;
		return db;
	}

	int get_population(const string& name)
	{
		return capitals[name];
	}

};

//this interface has a problem
//it is strongly coupled to the database.
//it handles the database directly
//meaning that it depends on the details of the implementation of the database so it is at risk of breaking if the database implementation changes.
struct SingletonRecordFinder
{
	int total_population(vector<string> names)
	{
		int result = 0;
		for (auto& name : names)
		{
			result += SingletonDatabase::get().get_population(name);
		}
		return result;
	}
};

//This implementation added the Database class, and made SingletonDatabase inherit from Database
//get_population became a virtual function in Database
//because polymorphism, can pass a SingletonDatabase as an argument in the constructor
//Since SingletonDatabase inherits from Database, you can call the get_population() member directly on it
//Making it so that if SingletonDatabase changes, as long as it implements the functions of Database which it inherits from.... all code will continue working
struct ConfigurableRecordFinder
{

	//this is how the dependency is injected. the db object contains a Database object that contains the member functions we want access to
	Database& db;
	//this allows us to stop using "SingletonDatabase::get()" - this dependency comes with the object

public:

	//by passing in a Database object we can call its members directly on the object instead of depending on the details of the SingletonDatabase implementation
	ConfigurableRecordFinder(Database& db) : db(db) {}

	int total_population(vector<string> names)
	{
		int result = 0;
		for (auto& name : names)
		{
			result += db.get_population(name);
		}
		return result;
	}

};

int main(void)
{
	string city = "Tokyo";
	cout << city << " has a population of: " << SingletonDatabase::get().get_population(city) << endl;

	SingletonRecordFinder srf; 
	int population = srf.total_population(vector<string>{ "Tokyo", "Seoul", "New York" });

	cout << "population total: " << population << endl;
	return 0;
}