//virual proxy gives you the impression that you are working with the original object
//even if it has not yet been created

#include <string>
#include <iostream>

using namespace std;

struct Image
{
	virtual void draw() = 0;
};

struct Bitmap : Image
{
	Bitmap(const string& filename)
	{
		cout << "Loading bitmap from " << filename << endl;
	}

	void draw() override
	{
		cout << "Drawing bitmap" << endl;
	}

};


//LazyBitmap is what we use in place of Bitmap so that we can add control ontop of Bitmap.
//Doing this in this case allows us to only create a Bitmap object when it needs to be drawn
struct LazyBitmap : Image
{
	LazyBitmap(const string& filename) : filename(filename) 
	{
		
	}

	void draw() override
	{
		if (!bmp)
		{
			bmp = new Bitmap(filename);
		}
		bmp->draw();
	}

private:
	string filename;
	Bitmap* bmp{ nullptr };
};

int main()
{
	Bitmap bmp("pokemon.png");

	return 0;
}