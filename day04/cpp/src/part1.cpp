#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>

struct entry {
	std::string field;
	std::string value;
};

std::vector<entry> get_entries(const std::string &pentry) {
	std::vector<entry> entries;

	std::stringstream ss(pentry);
	std::string part;
	while (std::getline(ss, part, ' ')) {
		std::string field = part.substr(0, part.find(':'));
		std::string value = part.substr(part.find(':') + 1);
		entries.push_back(entry{field, value});
	}

	return entries;
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

	std::set<std::string> mandatory = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
	std::vector<std::string> passports;

	size_t valid = 0, not_valid = 0;
	std::string line, passport = "";
	while (std::getline(infile, line)) {

		if (line.empty()) {
			passports.push_back(passport);

			// reset
			passport = "";
		}
		else
			passport += line + " ";
	}
	if (line.empty())
		passports.push_back(passport);


	for (const std::string &p : passports) {
		std::vector<entry> entries = get_entries(p);
		std::set<std::string> fields;
		for (const entry &e : entries)
			fields.insert(e.field);

		if (std::all_of(mandatory.begin(), mandatory.end(), 
				[&](const std::string &f) { return (fields.find(f)
							!= fields.end()); }))
			++valid;
		else 
			++not_valid;

		// reset
		passport = "";
	}

	std::cout << "There are " << valid << " valid passports\n";
	std::cout << "There are " << not_valid << " not valid passports\n";
	return 0;
}
