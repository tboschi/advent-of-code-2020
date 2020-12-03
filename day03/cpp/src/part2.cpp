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

	std::vector<size_t> x = {1, 3, 5, 7, 1};
	std::vector<size_t> y = {1, 1, 1, 1, 2};

	size_t result = 1;
	std::vector<size_t> trees(x.size());
	for (size_t run = 0; run < x.size(); ++run) {

		std::string slope;
		size_t cx = 0, cy = 0, trees = 0;
		while (std::getline(infile, slope)) {

			if (cy++ % y[run])
				continue;

			if (slope[cx % slope.length()] == '#')
				++trees;
			cx += x[run];
		}
		std::cout << "Going " << y[run] << " down and " << x[run] << " right"
			 " you hit " << trees << " trees\n";
		result *= trees;

		// go back at the beginning again
		infile.clear();
		infile.seekg(0, std::ios::beg);
	}

	std::cout << "Result is " << result << "\n";

	return 0;
}
