#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> readFileLines(const std::string& filePath);

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	const std::vector<std::string> lines { readFileLines(argv[1]) };
	if (lines.size() == 0) throw std::runtime_error("Bad input file - file was empty");

	std::vector<size_t> beams;

	for (const char& c : lines[0]) {
		if (c == '.') beams.push_back(0);
		else if (c == 'S') beams.push_back(1);
		else throw std::runtime_error("Bad input file - first line must contain only '.' and 'S'");
	}

	for (unsigned int i = 1; i < lines.size(); i++) {
		const std::string& line = lines[i];

		if (line.length() != beams.size()) throw std::runtime_error("Bad input file - all lines must be of equal length");
		if (line[0] != '.') throw std::runtime_error("Bad input file - all lines must start with '.'");
		if (line[line.length() - 1] != '.') throw std::runtime_error("Bad input file - all lines must end with '.'");

		std::vector<size_t> newBeams;
		for (unsigned int j = 0; j < beams.size(); j++) newBeams.push_back(0);

		for (unsigned int j = 0; j < line.length(); j++) {
			if (line[j] == '.') {
				if (beams[j]) newBeams[j] += beams[j];
			} else if (line[j] == '^') {
				if (line[j - 1] == '^' || line[j + 1] == '^') throw std::runtime_error("Bad input file - consecutive '^'s not allowed");

				if (beams[j]) {
					newBeams[j - 1] += beams[j];
					newBeams[j + 1] += beams[j];
				}
			} else throw std::runtime_error("Bad input file - lines after the first must contain only '.' and '^'");
		}

		beams = newBeams;
	}

	size_t total { 0 };

	for (size_t possibilities : beams) total += possibilities;

	std::cout << total << std::endl;

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