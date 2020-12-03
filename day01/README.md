# Day 1

The puzzle for [Day 1](https://adventofcode.com/2020/day/1)

## Algorithm

### Part 1
The **input** file is looped over and an ordered container (vector in C++, list in python, slice in go) is filled with the integer conversion of each line, the value `cost`.
At the same time the value `2020 - cost` is searched for in the same container.
If this value is found, then the pair of costs in the input file which sum up to 2020 is determined and the program quits.
As the solution is unique, there is no need to loop over the entire input file.

### Part 2
The **input** file is looped over and an ordered container `costs` (vector in C++, list in python, slice in go) is filled with the integer conversion of each line, the cost value `x`.
At the same time, `costs` is loop over too, up to the second to last value, as cost value `y` and the value `2020 - x - y` is searched for in `costs`.
If this value is found, then the three cost values which sum up to 2020 are determined and the program quits.
As the solution is unique, there is no need to loop over the entire input file.

## Compile and get the solution

For the C++ implementation
```
make cpp
./cpp/part1 input
./cpp/part2 input
```

For the python implementation
```
./py/part1 input
./py/part2 input
```

For the go implementation
```
./go/part1 input
```
