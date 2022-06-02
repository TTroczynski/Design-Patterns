#include <iostream>

class Rectangle{

protected:
	int width;
	int height;

public:
	Rectangle(int width, int height) : height(height), width(width) {}

	virtual void setWidth(int width) {
		this->width = width;
	}
	virtual void setHeight(int height) {
		this->height = height;
	}
	int getWidth() {
		return width;
	}
	int getHeight(){
		return height;
	}
	int area() const {
		return width * height;
	}
};

void process(Rectangle& r) {
	int w = r.getWidth();
	r.setHeight(10);

	std::cout << "expected area = " << (w * 10) << ", got " << r.area() << std::endl;
}

class Square : public Rectangle {
protected:
	int side;
public:
	Square(int side) : Rectangle(side, side) {}

	void setWidth(int width) override {
		this->width = this->height = width;
	}

	void setHeight(int height) override {
		this->height = this->width = height;
	}

	int area() {
		return width * height;
	}
};


int main(void) {
	Rectangle r{ 3,4 };
	process(r);

	Square sq{ 5 };
	process(sq);
}