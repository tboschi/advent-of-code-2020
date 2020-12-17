#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

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

	size_t c = 0;
	int speak = 0, last = -1;

	std::string line;
	std::unordered_map<int, int> rounds;
	while (std::getline(infile, line, ',')) {
		if (c > 0)
			rounds[last] = c;
		++c;

		speak = std::stoi(line);
		std::cout << c << " say: " << speak << "\n";
		last = speak;
	}

	for (size_t i = c; i < 2020; ++i) {
		auto rl = rounds.find(last);
		if (rl == rounds.end()) {
			rounds.insert(rounds.end(), {last, i});
			last = 0;
			//std::cout << i+1 << " say: " << 0 << "\n";
		}
		else {
			last = i - rl->second;
			rl->second = i;
			//std::cout << i+1 << " say: " << last << "\n";
		}
	}	

	std::cout << "Last round is " << last << "\n";

	return 0;
}
