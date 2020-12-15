#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
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

	std::string line;
	std::getline(infile, line);
	size_t est_time = std::stoi(line);
	std::vector<int> buses;
	while (std::getline(infile, line, ',')) {
		int bus;
		std::stringstream ss(line);
		if (ss >> bus)
			buses.push_back(bus);
	}

	size_t bus_i = 0;
	int eta = buses[bus_i] - est_time % buses[bus_i];
	for (size_t i = 1; i < buses.size(); ++i) {
		if (buses[i] - est_time % buses[i] < eta) {
			eta = buses[i] - est_time % buses[i];
			bus_i = i;
		}
	}	

	std::cout << "The first bus is # " << buses[bus_i] << "\n";
	std::cout << "The answer is " << buses[bus_i] * eta << "\n";

	return 0;
}
