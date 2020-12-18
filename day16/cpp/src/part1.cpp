#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using rule = std::vector<std::pair<int, int> >;
using ticket = std::vector<int>;

// field is invalid if not contained in any interval
bool valid(const rule &r, int field) {
	return std::any_of(r.begin(), r.end(),
		[=](const std::pair<int, int> &lim) {
			return lim.first <= field && field <= lim.second;
			});
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

	size_t c = 0;
	int speak = 0, last = -1;

	std::map<std::string, rule> rules;
	ticket my;
	std::vector<ticket> nearby;

	std::string line;
	while (std::getline(infile, line)) {
		if (line.empty())
			continue;

		// process my ticket
		if (line.find("your") != std::string::npos) {
			std::getline(infile, line);
			std::stringstream ssl(line);
			std::string val;
			while(std::getline(ssl, val, ','))
				my.push_back(std::stoi(val));
			continue;
		}
		// process other tickets
		else if (line.find("nearby") != std::string::npos) {
			while (std::getline(infile, line)) {
				std::stringstream ssl(line);
				std::string val;
				ticket other;
				while(std::getline(ssl, val, ','))
					other.push_back(std::stoi(val));
				nearby.push_back(other);
			}
			continue;
		}

		// process rules
		std::stringstream ssl(line);
		std::string rulename;
		std::getline(ssl, rulename, ':');

		rule r;
		std::string lim1, lim2;
		while (!ssl.eof()) {
			if (std::isdigit(ssl.peek())) {
				std::getline(ssl, lim1, '-');
				std::getline(ssl, lim2, ' ');
				r.emplace_back(std::stoi(lim1), std::stoi(lim2));
			}
			else
				ssl.ignore();
		}
		rules[rulename] = std::move(r);
	}


	// check if loaded correctly
	/*
	for (const auto r : rules) {
		std::cout << "rules for " << r.first << "\n";
		for (const auto p : r.second)
			std::cout << "\t" << p.first << "-" << p.second;
		std::cout << "\n";
	}
	std::cout << "nearby tickets are " << nearby.size() << "\n";
	*/

	// control nearby tickets
	size_t error = 0;
	for (const auto &n : nearby)
		for (int f : n) {	// check fields
			if (std::all_of(rules.begin(), rules.end(),
					[=](const std::pair<std::string, rule> &r) {
						return !valid(r.second, f); } )) {
				error += f;
			}
		}

	std::cout << "Error scanning rate is " << error << "\n";
	return 0;
}
