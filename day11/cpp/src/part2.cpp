#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>

using floormap = std::vector<std::string>;

// cont number of occupied seats around x, y
size_t check(const floormap &state, size_t x, size_t y) {
	size_t busy = 0;
	long int i = y, j = x;
	// vertical directions first
	while (i > 0 && state[--i][x] == '.');
	if (y > 0) 
		busy += (state[i][x] == '#');
	i = y;

	while (i < state.size()-1 && state[++i][x] == '.');
	if (y < state.size()-1)
		busy += (state[i][x] == '#');
	i = y;

	// horizontal directions
	while (j > 0 && state[y][--j] == '.');
	if (x > 0)
		busy += (state[y][j] == '#');
	j = x;

	while (j < state[y].size()-1 && state[y][++j] == '.');
	if (x < state[y].size()-1)
		busy += (state[y][j] == '#');
	j = x;

	// diagonal directions
	while (i > 0 && j > 0 && state[--i][--j] == '.');
	if (y > 0 && x > 0)
		busy += (state[i][j] == '#');
	i = y; j = x;

	while (i < state.size()-1 && j < state[y].size()-1 && state[++i][++j] == '.');
	if (y < state.size()-1 && x < state[y].size()-1)
		busy += (state[i][j] == '#');
	i = y; j = x;

	// anti diagonal directions
	while (i < state.size()-1 && j > 0 && state[++i][--j] == '.');
	if (y < state.size()-1 && x > 0)
		busy += (state[i][j] == '#');
	i = y; j = x;

	while (i > 0 && j < state[y].size()-1 && state[--i][++j] == '.');
	if (y > 0 && x < state[y].size()-1)
		busy += (state[i][j] == '#');
	i = y; j = x;

	return busy;
}

floormap next(const floormap &state) {
	floormap newstate = state;
	for (size_t y = 0; y < newstate.size(); ++y) {
		for (size_t x = 0; x < newstate[y].size(); ++x) {
			if (state[y][x] == '.')
				continue;

			size_t occupied = check(state, x, y);
			if (state[y][x] == 'L' && occupied == 0)
				newstate[y][x] = '#';
			else if (state[y][x] == '#' && occupied >= 5)
				newstate[y][x] = 'L';
		}
	}
	return newstate;
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
	std::vector<std::string> seats;
	std::string line;
	while (std::getline(infile, line)) {
		seats.push_back(line);
	}

	std::vector<std::string> next_seats(seats.size());
	bool diff = true;
	while (diff) {
		next_seats = next(seats);
		diff = false;
		for (size_t i = 0; i < seats.size(); ++i)
			if (diff = (seats[i] != next_seats[i]))
				break;
		seats = next_seats;
	}

	size_t occupied = std::accumulate(next_seats.begin(), next_seats.end(), 0,
			[](size_t sum, const std::string &sit) {
				return sum + std::count(sit.begin(), sit.end(), '#');
			} );
	std::cout << "There are " << occupied << " occupied seats\n";

	return 0;
}
