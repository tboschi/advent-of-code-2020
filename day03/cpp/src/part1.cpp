#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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

	std::string slope;
	size_t x = 0;
	size_t trees = 0;
	while (std::getline(infile, slope)) {

		if (slope[x % slope.length()] == '#')
			++trees;
		x += 3;
	}

	std::cout << "You hit " << trees << " trees\n";
	return 0;
}
