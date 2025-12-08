#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cassert>

std::vector<std::string> readFileLines(const std::string& filePath);
size_t readSizeT(std::string& str);

class Range {
public:

	Range(size_t a, size_t b) :
		start { std::min(a, b) },
		end { std::max(a, b) }
	{}

	inline bool contains(size_t n) const {
		return valid ? (n >= start && n <= end) : false;
	}

	inline size_t size(void) const {
		return valid ? (end - start + 1) : 0;
	}

	void combine(Range& other) {
		if (!valid) return;
		if (!other.valid) return;

		if (contains(other.start) && contains(other.end)) {
			other.valid = false;
			return;
		}

		if (other.contains(start) && other.contains(end)) {
			valid = false;
			return;
		}

		if (contains(other.start)) {
			assert(!contains(other.end));

			end = other.start - 1;
			return;
		}

		if (contains(other.end)) {
			assert(!contains(other.start));

			start = other.end + 1;
			return;
		}

		assert(!other.contains(start));
		assert(!other.contains(end));
	}

	size_t start, end;
	bool valid { true };
};

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	std::vector<std::string> lines = readFileLines(argv[1]);
	if (lines.size() == 0) throw std::runtime_error("Bad input file - file was empty");

	std::vector<Range> ranges {};

	for (std::string& line : lines) {
		if (!line.length()) break;

		const size_t start = readSizeT(line);

		if (!line.length()) throw std::runtime_error("Bad input file - range had only 1 number");
		if (line[0] != '-') throw std::runtime_error("Bad input file - range seperator must be '-'");
		line.erase(line.begin());
		if (!line.length()) throw std::runtime_error("Bad input file - range had only 1 number");

		const size_t end = readSizeT(line);
		if (line.length()) throw std::runtime_error("Bad input file - range had more than 2 numbers");

		ranges.emplace_back(start, end);
	}

	for (unsigned int i = 0; i < ranges.size(); i++) {
		for (unsigned int j = i + 1; j < ranges.size(); j++) {
			if (!ranges[i].valid) break;
			ranges[i].combine(ranges[j]);
		}
	}

	size_t total { 0 };

	for (const Range& range : ranges) {
		total += range.size();
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