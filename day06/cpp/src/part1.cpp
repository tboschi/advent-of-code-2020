#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

size_t answer_to_int(const std::string &s) {
	return std::accumulate(s.begin(), s.end(), 0,
		[](size_t res, unsigned char c) { return res + (1 << size_t(c - 'a') + 1); });
}

size_t hamming_weight(size_t val) {
	size_t res = val & 1;
	while (val = val >> 1)
		res += val & 1;
	return res;
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

	std::vector<std::vector<size_t> > groups;
	std::vector<size_t> group;
	std::string line;
	while (std::getline(infile, line)) {

		if (line.empty()) {
			groups.push_back(group);
			group.clear();
		}
		else
			group.push_back(answer_to_int(line));
	}
	// last one
	if (line.empty())
		groups.push_back(group);

	size_t total = 0;
	for (const auto &g : groups) {
		size_t all_answers = g.front();
		for (auto ig = std::next(g.begin()); ig != g.end(); ++ig)
			all_answers |= *ig;

		total += hamming_weight(all_answers);
	}
	std::cout << "Total number of \"yes\" answers is " << total << std::endl;
	return 0;
}
