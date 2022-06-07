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

using namespace std;

enum class Importance
{
	primary,
	secondary,
	tertiary
};


//works for all object types and keys
//stores multiple instances in a static map
//a singleton of multiple instances
template <typename T, typename Key = std::string>
class Multiton
{
public:
	static shared_ptr<T> get(const Key& key)
	{
		const auto it = instances.find(key);
		
		if (it != instances.end())
		{
			return it->second;
		}

		auto instance = make_shared<T>();
		instances[key] = instance;
		return instance;
	}
protected:
	Multiton() = default;
	virtual ~Multiton() = default;

private:
	static map < Key, shared_ptr<T>> instances;
};

template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;
//template for map


class Printer
{
public:
	Printer()
	{
		++Printer::totalInstanceCount;
		cout << "A total of " << Printer::totalInstanceCount << " instances created so far" << endl;
	}
private:
	static int totalInstanceCount;
};
int Printer::totalInstanceCount = 0;



int main(void)
{
	//Remember Singletons only prevent multiple instances of an object(Self).

	//A multiton sets up a key/value store, where you can restrict the number of elements that are 
	//included in the store and given out to the client.

	typedef Multiton<Printer, Importance> mt;

	auto main = mt::get(Importance::primary);
	auto aux = mt::get(Importance::secondary);
	auto aux2 = mt::get(Importance::secondary);
	//only 1 instance of a Printer with Importance::Secondary were created.
	//because there is only ONE enum member "secondary" and the map stores this field as a key

	return 0;
}