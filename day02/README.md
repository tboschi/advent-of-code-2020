# Day 2

The puzzle for [Day 2](https://adventofcode.com/2020/day/2)

## Algorithm and explanation

### Part 1
The **input** file is looped over and each line is separated in two parts: the *policy* (everything before the colon) and the *password* (everything else).
The two numbers in the policy *policy*, spearatade by a dash, are the minimum and maximum counts that the last character of the policy must appear in the password.
which corresponds to the an ordered container (vector in C++, list in python, slice in go) is filled with the integer conversion of each line, the value `cost`.
At the same time the value `2020 - cost` is searched for in the same container.
If this value is found, then the pair of costs in the input file which sum up to 2020 is determined and the program quits.
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
