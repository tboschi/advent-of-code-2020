#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>

// this function solves the equation
//	p0 * n0 = p1 * n1 - t
// finding the minimum values of n1 that satisfies it
// and p0 and p1 are prime numbers
// return n0
size_t solve(size_t p0, size_t p1, long int dt) {
	size_t n1 = 0;
	if (dt >= 0)
		n1 = dt / p1 + 1;
	size_t v = (p1 * n1 - dt) % p0;
	while (v != 0) {
		v = (v + p1) % p0;
		++n1;
	}
	size_t n0 = (p1 * n1 - dt) / p0;
	std::cout << p0 << " * " << n0 << " = " << p1 << " * " << n1
		  << " - " << dt << std::endl;
		
	return n0;
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

	std::string line;
	std::getline(infile, line);
	size_t est_time = std::stoi(line);
	std::vector<std::pair<int, int> > buses;
	int c = 0;
	while (std::getline(infile, line, ',')) {
		int bus;
		std::stringstream ss(line);
		if (ss >> bus)
			buses.emplace_back(bus, c);
		++c;
	}

	if (buses.size() <= 1)
		return 1;

	std::vector<long int> mul;
	mul.reserve(buses.size() - 1);
	for (size_t i = 1; i < buses.size(); ++i)
		mul.push_back(buses[i].second - buses[0].second);

	std::vector<long int> res;
	res.reserve(buses.size());
	res.push_back(-buses[0].second);
	for (size_t i = 0; i < buses.size()-1; ++i) {
		res.push_back(solve(buses[i].first, buses[i+1].first, mul[0]));
		std::vector<long int> mul2;
		mul2.reserve(buses.size() - i - 2);
		for (size_t j = i+2; j < buses.size(); ++j) {
			mul2.push_back(res.back() - solve(buses[i].first, buses[j].first, mul[j-i-1]));
						//- res.back());
		}
		mul = mul2;
	}

	size_t eta = 0;
	for (size_t i = 0; i < res.size(); ++i) {
		eta *= buses[res.size()-i-1].first;	
		eta += res[res.size()-i-1];
	}

	std::cout << "Smallest increment is " << eta << "\n";

	//bool keep = true;
	//size_t n = 
	//while (keep) {
		//for (size_t 
	//}

	return 0;
}
