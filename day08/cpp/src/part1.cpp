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

	std::set<int> visited;
	int acc = 0;
	int i = 0;
	while (i < instructions.size()) {
		if (!visited.insert(i).second) {
			std::cout << "Operation " << instructions[i].first
				  << " " << instructions[i].second
				  << " already visited\n";
			break;
		}

		if (instructions[i].first == "acc") {
			acc += instructions[i].second;
			++i;
		}
		else if (instructions[i].first == "jmp")
			i += instructions[i].second;
		else
			++i;
	}

	std::cout << "The accumulator is at " << acc << "\n";

	return 0;
}
