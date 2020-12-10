#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

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

	// add 0 at the beginning, which is the outlet jolts rate
	std::vector<size_t> adaptors(1);
	std::string line;
	while (std::getline(infile, line)) {

		std::stringstream ssl(line);
		size_t jolts;
		ssl >> jolts;
		adaptors.push_back(jolts);
	}

	std::sort(adaptors.begin(), adaptors.end());

	// add built-in device jolts rate
	adaptors.push_back(adaptors.back() + 3);

	std::map<int, int> differences;
	for (size_t i = 1; i < adaptors.size(); ++i)
		++differences[adaptors[i] - adaptors[i-1]];

	for (const auto &id : differences)
		std::cout << "Difference " << id.first
			  << " : " << id.second << "\n";

	std::cout << "Result is " << differences[1] * differences[3] << std::endl;

	return 0;
}
