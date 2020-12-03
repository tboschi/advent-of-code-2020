#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
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

	std::vector<int> costs;
	std::string line;
	while (std::getline(infile, line)) {
		std::stringstream ss(line);
		int x;
		ss >> x;

		// storing x and looking for 2020 - x in vector
		costs.push_back(x);
		auto z = std::find(costs.begin(), costs.end()-1, 2020 - x);
		if (z != costs.end()-1) {
			std::cout << "Found! " << x << " + " << *z
				  << " = " << x + *z << "\n";
			std::cout << "Result is " << x * (*z) << "\n";
			return 0;
		}
		// there is no need to load the full file
	}

	std::cout << "Did not found anything...\n";
	return 1;
}
