#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

using rule = std::map<std::string, int>;

static const std::string key_color = "shiny gold";

bool check_in_bag(std::string color, const std::map<std::string, rule> &rules) {
	if (rules.at(color).count(key_color))
		return true;

	return std::any_of(rules.at(color).begin(), rules.at(color).end(),
			[&](const std::pair<std::string, int> &rr) {
				return check_in_bag(rr.first, rules);
			} );
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

	std::map<std::string, rule> rules;
	std::string line;
	while (std::getline(infile, line)) {

		// remove last element '.'
		line.erase(std::prev(line.end()));
		// remove all ','
		std::replace(line.begin(), line.end(), ',', ' ');

		std::stringstream ssl(line);
		std::vector<std::string> words;
		std::string word;
		while (ssl >> word)
			words.push_back(word);

		// create rule
		rule rr;
		std::string color = words[0] + " " + words[1];
		for (size_t i = 0; i < words.size() / 4 - 1; ++i) {
			int quantity = std::stoi(words[4*(i+1)]);
			std::string in_col = words[4*(i+1) + 1] + " " + words[4*(i+1) + 2];
			rr[in_col] = quantity;
		}

		rules[color] = std::move(rr);
	}

	size_t valid = 0;
	for (const auto &rr : rules)
		if (check_in_bag(rr.first, rules)) {
			std::cout << "A " << rr.first << " bag can contain a " << key_color << " one\n";
			++valid;
		}

	std::cout << "There are " << valid << " valid bags\n";


	return 0;
}
