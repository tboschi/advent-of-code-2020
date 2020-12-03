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

	// need to load full file this round
	std::vector<int> costs;
	std::string line;
	while (std::getline(infile, line)) {
		std::stringstream ss(line);
		int x;
		ss >> x;

		//storing x
		costs.push_back(x);
		for (auto y = costs.begin(); y != std::prev(costs.end()); ++y) {
			auto z = std::find(std::next(y), std::prev(costs.end()),
						2020 - x - *y);
			if (z != std::prev(costs.end())) {
				std::cout << "Found! " << x << " + " << *y
					<< " + " << *z << " = "
					<< x + *y + *z << "\n";
				std::cout << "Result is " << x * (*y) * (*z) << "\n";
				return 0;
			}
		}
	}

	std::cout << "Did not found anything...\n";
	return 1;
}
