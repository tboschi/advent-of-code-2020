#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

	std::string line;
	int valid = 0, not_valid = 0;
	while (std::getline(infile, line)) {
		std::stringstream ss(line);
		std::string policy, sep, password;
		ss >> policy >> sep >> password;

		// extract min and max counts from policy string
		std::stringstream pp(policy);
		std::vector<int> counts;
		counts.reserve(2);
		while (std::getline(pp, policy, '-'))
			counts.push_back(std::stoi(policy));

		//remove : from key
		char key = sep[0];

		if (std::count(password.begin(), password.end(), key) >= counts[0]
		  && std::count(password.begin(), password.end(), key) <= counts[1]) {
			std::cout << "\'" << line << "\' is valid\n";
			++valid;
		}
		else
			std::cout << "\'" << line << "\' is not valid\n";
			++not_valid;
	}

	std::cout << "There are " << valid << " valid passwords\n";
	return 1;
}
