#include <string>
#include <vector>
#include <fstream>

class Journal {

	std::string title;
	std::vector<std::string> entries;

	

public:
	Journal(const std::string& title) : title(title) {}
	void add_Entry(const std::string& entry) {

		static int count = 1;
		entries.push_back(std::to_string(count++) + ": " + entry);
	}

	std::vector<std::string> get_Entries() {
		return entries;
	}
	
};

class PersistanceManager {

public:
	static void save(Journal& j, const std::string& filename) {
		std::ofstream ofs;
		for (auto& entry : j.get_Entries()) {
			ofs << entry << std::endl;
		}
	}
};

int main(void) {
	
	Journal journal("Diary");

	journal.add_Entry("I ate a bug");
	journal.add_Entry("I am sad"); 

	PersistanceManager pm;

	pm.save(journal, "journal.txt"); 


	return 0;
}