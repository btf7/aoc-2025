#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

std::vector<std::string> readFileLines(const std::string& filePath);

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	const std::vector<std::string> lines = readFileLines(argv[1]);

	int total{ 0 };

	for (const std::string& line : lines) {
		if (line.length() < 2) throw std::runtime_error("Bad input file - line must contain at least 2 characters");
		for (const char& c : line) {
			if (!isdigit(c)) throw std::runtime_error("Bad input file - line must consist of numbers");
		}

		int maxI{ 0 };
		for (unsigned int i = 1; i < line.length() - 1; i++) {
			if (line[i] > line[maxI]) maxI = i;
		}

		int joltage{ (line[maxI] - '0') * 10 };

		maxI++;

		for (unsigned int i = maxI + 1; i < line.length(); i++) {
			if (line[i] > line[maxI]) maxI = i;
		}

		joltage += line[maxI] - '0';
		total += joltage;
	}

	std::cout << total << std::endl;

	return 0;
}

std::vector<std::string> readFileLines(const std::string& filePath) {
	std::ifstream file;
	file.open(filePath);
	if (!file.is_open()) throw std::runtime_error("Failed to open file \"" + filePath + "\"");

	std::vector<std::string> lines;
	std::string line;
	while (getline(file, line)) {
		if (line.length()) lines.push_back(line);
	}

	file.close();

	return lines;
}