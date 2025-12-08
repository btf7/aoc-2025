#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

std::vector<std::string> readFileLines(const std::string& filePath);
size_t readSizeT(std::string& str);

class Range {
public:

	Range(size_t start, size_t end) :
		_start { start },
		_end { end }
	{}

	inline bool contains(size_t n) const {
		return n >= _start && n <= _end;
	}

private:

	const size_t _start, _end;
};

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	std::vector<std::string> lines = readFileLines(argv[1]);
	if (lines.size() == 0) throw std::runtime_error("Bad input file - file was empty");

	std::vector<Range> ranges {};

	for (std::string& line : lines) {
		if (!line.length()) break; // Move onto IDs

		const size_t start = readSizeT(line);

		if (!line.length()) throw std::runtime_error("Bad input file - range had only 1 number");
		if (line[0] != '-') throw std::runtime_error("Bad input file - range seperator must be '-'");
		line.erase(line.begin());
		if (!line.length()) throw std::runtime_error("Bad input file - range had only 1 number");

		const size_t end = readSizeT(line);
		if (line.length()) throw std::runtime_error("Bad input file - range had more than 2 numbers");

		ranges.emplace_back(start, end);
	}

	if (lines.size() == ranges.size()) throw std::runtime_error("Bad input file - no IDs given");

	int total{ 0 };

	for (int i = ranges.size() + 1; i < lines.size(); i++) {
		std::string& line = lines[i];

		if (!line.length()) throw std::runtime_error("Bad input file - ID line was blank");

		const size_t val = readSizeT(line);

		if (line.length()) throw std::runtime_error("Bad input file - ID had more than 1 number");

		for (const Range& range : ranges) {
			if (range.contains(val)) {
				total ++;
				break;
			}
		}
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
		lines.push_back(line);
	}

	file.close();

	return lines;
}

size_t readSizeT(std::string& str) {
	size_t val { 0 };

	while (true) {
		if (!str.length()) break;
		if (!isdigit(str[0])) break;

		val *= 10;
		val += str[0] - '0';
		str.erase(str.begin());
	}

	return val;
}