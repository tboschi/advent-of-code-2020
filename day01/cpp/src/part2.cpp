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
	}

	// nested loop
	for (auto i = costs.begin(); i != costs.end(); ++i)
		for (auto j = std::next(i); j != costs.end(); ++j) {
			auto k = std::find(costs.begin(), costs.end(), 2020 - *i - *j);
			if (k != costs.end()) {
				std::cout << "Found! " << *i << " + " << *j
					<< " + " << *k << " = "
					<< *i + *j + *k << "\n";
				std::cout << "Result is " << (*i) * (*j) * (*k) << "\n";
				return 0;
			}
		}

	std::cout << "Did not found anything...\n";
	return 1;
}
