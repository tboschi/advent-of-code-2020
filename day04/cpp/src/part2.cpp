#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

typedef bool (*check_t)(const std::string &);

bool check_byr(const std::string &byr) {
	if (byr.length() != 4)
		return false;
	return (std::stoi(byr) >= 1920 && std::stoi(byr) <= 2002);
}

bool check_iyr(const std::string &iyr) {
	if (iyr.length() != 4)
		return false;
	return (std::stoi(iyr) >= 2010 && std::stoi(iyr) <= 2020);
}

bool check_eyr(const std::string &eyr) {
	if (eyr.length() != 4)
		return false;
	return (std::stoi(eyr) >= 2020 && std::stoi(eyr) <= 2030);
}

bool check_hgt(const std::string &hgt) {
	if (hgt.find("cm") != std::string::npos) {
		int hh = std::stoi(hgt.substr(0, hgt.find("cm")));
		return (hh >= 150 && hh <= 193);
	}

	if (hgt.find("in") != std::string::npos) {
		int hh = std::stoi(hgt.substr(0, hgt.find("in")));
		return (hh >= 59 && hh <= 76);
	}

	return false;
}

bool check_hcl(const std::string &hcl) {
    if (hcl[0] == '#') {
	    std::string var(hcl.begin()+1, hcl.end());
	    std::stringstream ss;
	    try {
	    	ss << std::hex << var;
	    }
	    catch (...) {
		    return false;
	    }

	    return true;
    }
    return false;
}

bool check_ecl(const std::string &ecl) {
	std::set<std::string> types = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
	return (types.find(ecl) != types.end());
}

bool check_pid(const std::string &pid) {
	return pid.length() == 9;
}

bool check_cid(const std::string &cid) {
	return true;
}

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
	std::map<std::string, check_t> checks = { {"byr", &check_byr},
						  {"iyr", &check_iyr},
						  {"eyr", &check_eyr},
						  {"hgt", &check_hgt},
						  {"hcl", &check_hcl},
						  {"ecl", &check_ecl},
						  {"pid", &check_pid},
						  {"cid", &check_cid} };
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
					!= fields.end()); })
		 && std::all_of(entries.begin(), entries.end(), 
				[&](const entry &e) { return (*checks[e.field])(e.value); }))
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
