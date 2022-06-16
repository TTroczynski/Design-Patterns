//Flyweight - used to avoid redundancy when storing data.

//when storing lots of data, you want to avoid storing repeating data
//lost of users with the same first and last names.
		//you could store pointers to those names instead

//working with text and you want to format the individual characters
//like making them bold, italicized...
//dont want to store additional information per character, when you bold things you do it on entire words
//		so you might use ranges to specify line number, start/end positions 

//flyweight saves memory by storing externally the data associated with similar objects.

#include <string>
#include <iostream>
#include <map>
#include <boost/bimap.hpp>


using namespace std;
using namespace boost;

typedef uint32_t key;

struct User
{
public:

	User(const string& first_name, const string& last_name) : first_name(add(first_name)), last_name(add(last_name)) {}

	const string& get_first_name() const
	{
		return names.left.find(first_name)->second;
	}

	const string& get_last_name() const
	{
		return names.left.find(last_name)->second;
	}

protected:
	key first_name, last_name;
	static bimap<key, string> names;
	static key seed;

	static key add(const string& s)
	{
		auto it = names.right.find(s);
		if (it == names.right.end())
		{
			key id = ++seed;
			names.insert({ seed, s });
			return id;
		}
		return it->second;
	}
};

key User::seed(0);
bimap<key, string> User::names;

ostream& operator<<(ostream& os, const User& user)
{
	os << "first name: " << user.get_first_name() << " last name: " << user.get_last_name() 
		<<  endl;
	return os;
}

int main(int ac, char* av[])
{
	User user1("John", "Smith");
	User user2("Jane", "Smith");


	//if you debug and step through the program, you will find that both last names 'Smith' correspond to the same
	//'Smith' in the 'names' bimap - same seed
	cout << user1 << endl << user2 << endl;

	return 0;
}