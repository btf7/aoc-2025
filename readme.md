# Advent of Code 2025

All of my solutions for AoC 2025, written in C++ and built with CMake.

If any of my solutions are strange or long-winded, it's because I made no reference to anyone else's solutions, didn't google any algorithms, am relatively new to the language, and copied code from previous days in the interest of saving time.
My aim with AoC is not to write the fastest and most optimised programs, but just to get all of the stars.

## Build

1.	Some solutions (for example day 8 part 1) have a parameter that changes between the test input and real input. For day 8 part 1, this is changing between making 10 pairs or 1000 pairs.
	In any solution where this is needed, the parameter will be set in a `constexpr` variable at the top of the file. Make sure you update this to match before building.

1.	From the folder for whichever day you want to build, create a build folder
	```
	.../aoc-2025/1$ mkdir build
	.../aoc-2025/1$
	```

1.	From your build folder, run `cmake ..` followed by `cmake --build .`
	```
	.../aoc-2025/1$ cd build
	.../aoc-2025/1/build$ cmake ..
	.../aoc-2025/1/build$ cmake --build .
	.../aoc-2025/1/build$
	```

1.	This will create executables `1` and `2`, for part 1 and part 2 of the problem respectively.
	Run with `./1 <inputfilepath>` or `./2 <inputfilepath>`
	```
	.../aoc-2025/1/build$ ./1 ../testinput1.txt
	3
	.../aoc-2025/1/build$
	```

Note that builds have only been tested on Debian 13 with g++ 14.2.0 and CMake 3.31.6, but should work on any platform, with any compiler, and on an older version of CMake.
The CMakeLists.txt files specify C++20, but older versions will probably still work.