#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

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

	std::vector<size_t> arrangements;
	arrangements.push_back(1);
	for (size_t i = 1; i < adaptors.size(); ++i) {
		long int j = i - 1;
		size_t arrange = arrangements[j];
		while (--j >= 0 && adaptors[i] - adaptors[j] <= 3)
			arrange += arrangements[j];

		arrangements.push_back(arrange); 
	}

	std::cout << "There are " << arrangements.back() << " valid arrangements\n";

	return 0;
}
