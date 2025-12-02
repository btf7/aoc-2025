#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <sstream>

std::string readFile(const std::string& filePath);
std::vector<std::string> splitString(const std::string& str, char delim);

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	const std::string file = readFile(argv[1]);
	const std::vector<std::string> rangeStrs{ splitString(file, ',') };
	size_t total{ 0 };

	for (const std::string& rangeStr : rangeStrs) {
		const std::vector<std::string> numStrs{ splitString(rangeStr, '-') };
		if (numStrs.size() != 2) throw std::runtime_error("Bad input file - range doesn't have 2 values");

		for (const std::string& numStr : numStrs) {
			for (const char& c : numStr) {
				if (!isdigit(c)) throw std::runtime_error("Bad input file - range contains non number character");
			}
		}

		const size_t first{ std::stoull(numStrs[0]) };
		const size_t last{ std::stoull(numStrs[1]) };

		for (size_t i = first; i <= last; i++) {
			const std::string str = std::to_string(i);

			if (str.length() % 2 == 1) continue;

			bool valid{ false };
			for (size_t j = 0; j < str.length() / 2; j++) {
				if (str[j] != str[j + str.length() / 2]) {
					valid = true;
					break;
				}
			}

			if (!valid) total += i;
		}
	}

	std::cout << total << std::endl;

	return 0;
}

std::string readFile(const std::string& filePath) {
	std::ifstream file;
	file.open(filePath);
	if (!file.is_open()) throw std::runtime_error("Failed to open file \"" + filePath + "\"");

	std::string str{ "" };
	std::string line;
	while (getline(file, line)) {
		if (line.length()) str += line;
	}

	file.close();

	return str;
}

std::vector<std::string> splitString(const std::string& str, char delim) {
	std::stringstream stream(str);
	std::string substr;
	std::vector<std::string> splitStrs;

	while (getline(stream, substr, delim)) {
		splitStrs.push_back(substr);
	}

	return splitStrs;
}