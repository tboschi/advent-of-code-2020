#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>


int main(int argc, char** argv) {
	if (argc < 1) {
		std::cerr << "Input file expected\n";
		return 1;
	}

	// read file
	std::ifstream infile(argv[1]);
	if (!infile.good()) {
		std::cerr << "Input file " << argv[1] << " does not exist\n";
		return 1;
	}

	std::vector<std::pair<std::string, int> > instructions;
	std::string line;
	while (std::getline(infile, line)) {

		std::stringstream ssl(line);
		std::string action;
		int value;

		ssl >> action >> value;
		std::pair<std::string, int> instr = std::make_pair(action, value);
		instructions.push_back(instr);
	}

	std::set<int> visited, changed;
	int acc = 0;
	int i = 0, wrong = 0;
	bool edited = false;
	while (i < instructions.size()) {
		if (!visited.insert(i).second) {
			std::cout << "Operation " << i << " (" << instructions[i].first
				  << " " << instructions[i].second
				  << ") already visited\n";
			// restart
			visited.clear();
			acc = 0;
			i = 0;
			edited = false;
		}

		if (instructions[i].first == "acc") {
			acc += instructions[i].second;
			++i;
		}
		else if (instructions[i].first == "jmp") {
			if (!edited && changed.insert(i).second)
			{
				wrong = i;
				edited = true;
				++i;
			}
			else
				i += instructions[i].second;
		}
		else {
			if (!edited && changed.insert(i).second)
			{
				wrong = i;
				edited = true;
				i += instructions[i].second;
			}
			else
				++i;
		}
	}

	std::cout << "Operation to change is " << wrong << " ("
		  << instructions[wrong].first << " " << instructions[wrong].second << ")\n";
	std::cout << "The accumulator is at " << acc << "\n";

	return 0;
}
