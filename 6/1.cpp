#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

std::vector<std::string> readFileLines(const std::string& filePath);
size_t readSizeT(std::string& str);
void readWhitespace(std::string& str);

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	std::vector<std::string> lines { readFileLines(argv[1]) };
	if (lines.size() == 0) throw std::runtime_error("Bad input file - file was empty");

	std::vector<std::vector<int>> rows;

	for (std::string& line : lines) {
		if (line.empty()) throw std::runtime_error("Bad input file - line was empty");

		if (line[0] == '+' || line[0] == '*') {
			size_t total { 0 };
			size_t i { 0 };

			while (true) {
				readWhitespace(line);
				if(line.empty()) break;

				if (rows[0].size() <= i) throw std::runtime_error("Bad input file - symbol row is too long");

				if (line[0] == '+') {
					size_t sum { 0 };
					for (const std::vector<int>& row : rows) {
						sum += row[i];
					}
					total += sum;
				} else if (line[0] == '*') {
					size_t product { 1 };
					for (const std::vector<int>& row : rows) {
						product *= row[i];
					}
					total += product;
				} else throw std::runtime_error("Bad input file - symbol row must be all '+' or '*'");

				line.erase(line.begin());
				i++;
			}

			std::cout << total << std::endl;

			break;
		} else {
			rows.push_back({});
			std::vector<int>& row = rows.back();

			while (true) {
				readWhitespace(line);
				if (line.empty()) break;

				row.push_back(readSizeT(line));
			}

			if (row.size() != rows[0].size()) throw std::runtime_error("Bad input file - not all rows are the same length");
		}
	}

	return 0;
}

std::vector<std::string> readFileLines(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) throw std::runtime_error("Failed to open file \"" + filePath + "\"");

	std::vector<std::string> lines;
	std::string line;
	while (getline(file, line)) {
		lines.push_back(line);
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

void readWhitespace(std::string& str) {
	while (true) {
		if (str.empty()) break;
		if (!isspace(str[0])) break;

		str.erase(str.begin());
	}
}