#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Neuron;

//CRTP - Curiously Repeating Template Pattern
template <typename Self>
struct SomeNeurons
{
	template <typename T> void connect_to(T& other)
	{
		//need to enumerate the neurons and the neurons of the 'other' argument
		//one is an extension of the vector stl container class and one is a neuron
		for (Neuron& from : *static_cast<Self*>(this)) // static cast casts the collection to iterate through
		{												// to the type being used through the template
			for (Neuron& to : other)
			{
				from.out.push_back(&to);
				to.in.push_back(&from);
			}
		}
	}
};


//a singular object posing as a collection
//by using the begin and end functions it can be used as a collection
//allows for creating abstractions or interfaces that are very clean when object A is singular and B is a collection
struct Neuron : SomeNeurons<Neuron>
{
	vector<Neuron*> in, out;
	unsigned int id;

	Neuron() 
	{
		static int id{ 1 };
		this->id = id++;
	}

	//because this Neuron is posing as a collection of elements in terms of the SomeNeurons interface...
	//the range based for-loops work for collection classes but this is not a collection class
	//it is a single object storing a network of neuron references
	Neuron* begin() { return this;  }
	Neuron* end() { return this + 1; }
	//these lines have the Neuron return itself when used as a collection

	//the 'this+1' is significant because... when the range based for-loop takes the begin() pointer
	//it will ++ it, which will result in this+1. It then compares the returneed value to the end to 
	//determine it is at the end
	//resulting in one Neuron pointer to this Neuron being iterated.

	friend ostream& operator<<(ostream& os, const Neuron& obj)
	{
		for (Neuron* n : obj.in)
		{
			os << n->id << "\t-->\t[" << obj.id << "]" << endl;
		}
		for (Neuron* n : obj.out)
		{
			os << "[" << obj.id << "]\t-->\t" << n->id << endl;
		}
		return os;
	
	}
};

//should never do this (inherit from STL types) because stl collection types dont have virtual destructors which can cause
//issues
//but to demonstrate a neuron layer...
struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
{
	NeuronLayer(int count)
	{
		while (count-- > 0)
		{
			emplace_back(Neuron{});
		}
	}
	friend ostream& operator<<(ostream& os, const NeuronLayer& obj)
	{
		for (auto& n : obj)
		{
			os << n;
			return os;
		}
	}
};


int main()
{
	Neuron n1, n2;
	n1.connect_to(n2);

	cout << n1 << n2 << endl;

	NeuronLayer layer1{ 2 }, layer2{ 3 };
	n1.connect_to(layer1);
	layer2.connect_to(n2);
	layer1.connect_to(layer2);
	//this explosion of possibilities for how to connect layers/neurons to neurons is not good
	//we want one way to handle these cases for us if possible.


	cout << layer1;

	return 0;
}