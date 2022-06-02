#include <string>
#include <vector>

enum Color { RED, GREEN, BLUE };
enum Size { SMALL, MEDIUM, LARGE};

struct Product {
	std::string name;
	Color color;
	Size size;
};

struct ProductFilter {
	std::vector<Product*> byColor(std::vector<Product*> items, Color color) {
		
		std::vector<Product*> result;
		for (auto& i : items) {
			if (i->color == color) {
				result.push_back(i);
			}
		}

		return result;
	}

	std::vector<Product*> bySize(std::vector<Product*> items, Size size) {

		std::vector<Product*> result;
		for (auto& i : items) {
			if (i->size == size) {
				result.push_back(i);
			}
		}

		return result;
	}


	template <typename T> struct Specification
	{
		virtual bool is_Satisfied(T* item) = 0;
	};

	template<typename T> struct Filter
	{
		virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) = 0;
	};

	struct ColorSpecification : Specification<Product> {
		Color color;

		ColorSpecification(Color color) : color(color) {}

		bool is_Satisfied(Product* item) override{
			if (item->color = color)
				return true;
		}
	};

	struct Betterfilter : Filter<Product> {
		std::vector<Product*> filter(std::vector<Product*> items, Specification<Product>& spec) override {
			std::vector<Product*> result;
			
			for (auto &i : items) {
				if (spec.is_Satisfied(i)) {
					result.push_back(i);
				}
			}

			return result;
		}
	};




	std::vector<Product*> bySizeAndColor(std::vector<Product*> items, Color color, Size size) {

		std::vector<Product*> result;
		for (auto& i : items) {
			if (i->color == color && i->size == size) {
				result.push_back(i);
			}
		}

		return result;
	}
};

int main(void) {

	Product apple{ "apple", Color::GREEN, Size::SMALL };
	Product tree{ "tree", Color::GREEN, Size::LARGE };
	Product house{ "house", Color::BLUE, Size::LARGE };

	std::vector<Product*> items{ &apple, &tree, &house };

	ProductFilter pf;
	auto greenThings = pf.byColor(items, Color::GREEN);
}