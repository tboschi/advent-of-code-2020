#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>

// cont number of occupied seats around x, y
void move_f(std::array<int, 2> &ship, const std::array<int, 2> &way, int units) {
	ship[0] += way[0] * units;
	ship[1] += way[1] * units;
}

void point(std::array<int, 2> &way, char act, int units)
{
	if (act == 'E')
		way[0] += units;
	else if (act == 'W')
		way[0] -= units;
	else if (act == 'N')
		way[1] += units;
	else if (act == 'S')
		way[1] -= units;
}

void rotate(std::array<int, 2> &way, int units)
{
	if (units == 1) {
		std::swap(way[0], way[1]);
		way[1] *= -1;
	}
	else if (units == 2) {
		way[0] *= -1;
		way[1] *= -1;
	}
	else if (units == 3) {
		std::swap(way[0], way[1]);
		way[0] *= -1;
	}
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
	std::array<int, 2> ship = {0, 0}, way = {10, 1};
	std::string line;
	while (std::getline(infile, line)) {
		char act = line[0];
		int units = std::stoi(std::string(line.begin()+1, line.end()));
		if (act == 'F')
			move_f(ship, way, units);
		else if (act == 'R')
			rotate(way, (units / 90) % 4);
		else if (act == 'L')
			rotate(way, (units / 30) % 4);
		else
			point(way, act, units);
	}
	std::cout << "The ship is at (" << ship[0] << ", " << ship[1]
	          << ") = " << std::abs(ship[0]) + std::abs(ship[1]) << "\n";

	return 0;
}
