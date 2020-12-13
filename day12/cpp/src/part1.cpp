#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>

using floormap = std::vector<std::string>;

const std::vector<char> rot = {'N', 'E', 'S', 'W'};

// cont number of occupied seats around x, y
void move_f(std::array<int, 2> &ship, char act, int units) {
	if (act == 'E')
		ship[0] += units;
	else if (act == 'W')
		ship[0] -= units;
	else if (act == 'N')
		ship[1] += units;
	else if (act == 'S')
		ship[1] -= units;
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

	// add 0 at the beginning, which is the outlet jolts rate
	std::array<int, 2> ship = {0, 0};
	std::string line;
	int dirs = 1;	// E
	while (std::getline(infile, line)) {
		char act = line[0];
		int units = std::stoi(std::string(line.begin()+1, line.end()));
		if (act == 'F')
			move_f(ship, rot[dirs], units);
		else if (act == 'R')
			dirs = (dirs + units / 90) % 4;
		else if (act == 'L')
			dirs = (dirs + units / 30) % 4;
		else
			move_f(ship, act, units);
	}
	std::cout << "The ship is at (" << ship[0] << ", " << ship[1]
	          << ") = " << std::abs(ship[0]) + std::abs(ship[1]) << "\n";

	return 0;
}
