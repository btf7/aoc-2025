#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

std::vector<std::string> readFileLines(const std::string& filePath);

struct Tile {
	bool paper{ false };
	u_int8_t neighbors{ 0 };
};

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	const std::vector<std::string> lines = readFileLines(argv[1]);
	if (lines.size() == 0) throw std::runtime_error("Bad input file - file was empty");
	// Each line is guaranteed to not be empty by readFileLines()

	const int height{ static_cast<int>(lines.size()) };
	const int width{ static_cast<int>(lines[0].size()) };
	Tile** tiles = new Tile*[height];
	for (int i = 0; i < height; i++) tiles[i] = new Tile[width];

	for (int i = 0; i < height; i++) {
		const std::string& line = lines[i];
		if (static_cast<int>(line.length()) != width) throw std::runtime_error("Bad input file - each line must be equal length");

		for (int j = 0; j < width; j++) {
			if (line[j] == '.') continue;
			else if (line[j] == '@') tiles[i][j].paper = true;
			else throw std::runtime_error("Bad input file - all chars must be '.' or '@'");
		}
	}

	int total{ 0 };
	int removed;

	do {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				tiles[i][j].neighbors = 0;
			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (tiles[i][j].paper) {
					for (int y = std::max(0, i - 1); y < std::min(height, i + 2); y++) {
						for (int x = std::max(0, j - 1); x < std::min(width, j + 2); x++) {
							if (y != i || x != j) tiles[y][x].neighbors++;
						}
					}
				}
			}
		}

		removed = 0;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Tile& tile = tiles[i][j];
				if (tile.paper && tile.neighbors < 4) {
					removed++;
					tile.paper = false;
				}
			}
		}

		total += removed;
	} while (removed);

	for (int i = 0; i < height; i++) delete[] tiles[i];
	delete[] tiles;

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