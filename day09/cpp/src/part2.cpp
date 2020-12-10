#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>

bool xmas(const std::vector<size_t> &data, size_t m) {
	if (m < 25)
		return true;
	for (size_t j = m - 25; j < m; ++j)
		for (size_t k = j+1; k < m; ++k)
			if (data[j] + data[k] == data[m])
				return true;
	return false;
}

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

	std::vector<size_t> data;
	std::string line;
	while (std::getline(infile, line)) {

		std::stringstream ssl(line);
		size_t value;
		ssl >> value;
		data.push_back(value);
	}

	size_t m = 25;
	for (; m < data.size(); ++m)
		if (!xmas(data, m))
			break;

	std::cout << "Looking for a range that sums up to " << data[m] << "\n";

	size_t i = 0, c = 0;
	for (; i < data.size(); ++i) {
		c = i;
		size_t sum = 0;
		while (sum < data[m])
			sum += data[c++];

		if (sum == data[m])
			break;
	}

	size_t small = data[i], large = data[i];
	for (size_t j = i+1; j < c; ++j) {
		if (data[j] < small)
			small = data[j];
		if (data[j] > large)
			large = data[j];
	}
		
	std::cout << "Result is " << small << " + " << large << " = " << small+large << "\n";

	return 0;
}
