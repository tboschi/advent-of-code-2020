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

	std::string bpass;
	size_t max_index = 0;
	std::vector<size_t> indices;
	while (std::getline(infile, bpass)) {

		std::transform(bpass.begin(), bpass.end(), bpass.begin(),
				[](unsigned char c) -> unsigned char {
					if (c == 'F' || c == 'L')
						return '0';
					else 
						return '1'; });

		size_t index = std::stoi(bpass, nullptr, 2);
		indices.push_back(index);
	}

	std::sort(indices.begin(), indices.end());
	for (auto ix = indices.begin(); ix != std::prev(indices.end()); ++ix)
		if (*std::next(ix) - *ix > 1) {
			std::cout << "There is an empty seat at " << *ix+1 << "\n";
			break;
		}

	return 0;
}
