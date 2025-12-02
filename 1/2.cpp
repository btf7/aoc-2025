#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

std::vector<std::string> readFileLines(const std::string& filePath);

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	const std::vector<std::string> lines = readFileLines(argv[1]);

	int dial{ 50 };
	int score{ 0 };

	for (const std::string& line : lines) {
		if(line.length() < 2) throw std::runtime_error("Bad file input - line not at least 2 characters long");

		const bool positive{ line[0] == 'R' };
		if (!positive && line[0] != 'L') throw std::runtime_error("Bad file input - line doesn't start with either 'L' or 'R'");

		int distance{ 0 };
		for (unsigned int i = 1; i < line.length(); i++) {
			if (!isdigit(line[i])) throw std::runtime_error("Bad file input - line doesn't contain number after 'L' or 'R'");

			distance *= 10;
			distance += line[i] - '0';
		}

		if (positive) {
			dial += distance;

			while (dial > 99) {
				dial -= 100;
				score++;
			}
		} else {
			const bool prev0{ dial == 0 };

			dial -= distance;

			if (dial < 0) {
				while (dial < 0) {
					dial += 100;
					score++;
				}
				if (prev0) score--;
			}

			if (dial == 0) score++;
		}
	}

	std::cout << score << std::endl;

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