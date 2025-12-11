#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> readFileLines(const std::string& filePath);
size_t readSizeT(std::string& str);

struct Position {
	int x, y;
};

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	std::vector<std::string> lines { readFileLines(argv[1]) };
	if (lines.size() < 2) throw std::runtime_error("Bad input file - file must contain at least 2 positions");

	std::vector<Position> positions {};

	for (std::string& line : lines) {
		const int x { static_cast<int>(readSizeT(line)) };

		if (line.empty()) throw std::runtime_error("Bad input file - lines must contain 2 numbers");
		if (line[0] != ',') throw std::runtime_error("Bad input file - numbers must be separated by ','");
		line.erase(line.begin());

		const int y { static_cast<int>(readSizeT(line)) };

		if (!line.empty()) throw std::runtime_error("Bad input file - lines must be empty past the 3rd number");

		positions.push_back({ x, y });
	}

	size_t maxArea { 0 };

	for (int i = 0; i < static_cast<int>(positions.size()); i++) {
		for (int j = i + 1; j < static_cast<int>(positions.size()); j++) {
			const size_t width = std::abs(positions[i].x - positions[j].x) + 1;
			const size_t height = std::abs(positions[i].y - positions[j].y) + 1;
			const size_t area = width * height;

			if (area > maxArea) maxArea = area;
		}
	}

	std::cout << maxArea << std::endl;

	return 0;
}

std::vector<std::string> readFileLines(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) throw std::runtime_error("Failed to open file \"" + filePath + "\"");

	std::vector<std::string> lines;
	std::string line;
	while (getline(file, line)) {
		if (!line.empty()) lines.push_back(line);
	}

	file.close();

	return lines;
}

size_t readSizeT(std::string& str) {
	size_t val { 0 };

	while (true) {
		if (str.empty()) break;
		if (!isdigit(str[0])) break;

		val *= 10;
		val += str[0] - '0';
		str.erase(str.begin());
	}

	return val;
}