#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cassert>

std::vector<std::string> readFileLines(const std::string& filePath);
size_t readSizeT(std::string& str);
int readWhitespace(std::string& str);

struct Equation {
	enum class Operator { Add, Multiply } op;
	std::vector<std::string> numStrs;
};

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	std::vector<std::string> lines { readFileLines(argv[1]) };
	if (lines.size() == 0) throw std::runtime_error("Bad input file - file was empty");

	std::vector<Equation> equations;
	std::string& opLine = lines.back();

	// The operator is always on the first character of any given chunk

	while (true) {
		equations.push_back({});
		Equation& equation = equations.back();

		if (opLine[0] == '+') equation.op = Equation::Operator::Add;
		else if (opLine[0] == '*') equation.op = Equation::Operator::Multiply;
		else throw std::runtime_error("Bad input file - operators must be '+' or '*'");

		opLine.erase(opLine.begin());

		const int spaces = readWhitespace(opLine);
		if (spaces == 0) throw std::runtime_error("Bad input file - operators must be separated");

		for (int i = 0; i < spaces; i++) equation.numStrs.push_back("");

		if (opLine.empty()) {
			equation.numStrs.push_back(""); // Last equation doesn't have the spacer so will be misread by 1
			break;
		}
	}

	size_t total { 0 };

	for (unsigned int i = 0; i < equations.size(); i++) {
		Equation& equation = equations[i];

		for (unsigned int j = 0; j < equation.numStrs.size(); j++) {
			for (unsigned int k = 0; k < lines.size() - 1; k++) {
				const char c = lines[k][0];

				if (!isspace(c)) equation.numStrs[j] += c;
				if (!lines[k].empty()) lines[k].erase(lines[k].begin()); // If this is the last equation, the line will be empty already
			}
		}

		// Remove blank column if this isn't the last equation
		if (i != equations.size() - 1) {
			for (unsigned int j = 0; j < lines.size() - 1; j++) lines[j].erase(lines[j].begin());
		}

		size_t localTotal = equation.op == Equation::Operator::Add ? 0 : 1;

		for (unsigned int j = 0; j < equation.numStrs.size(); j++) {
			assert(!equation.numStrs.empty());

			const size_t num = readSizeT(equation.numStrs[j]);
			if (equation.op == Equation::Operator::Add) localTotal += num;
			else localTotal *= num;
		}

		total += localTotal;
	}

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

int readWhitespace(std::string& str) {
	int chars { 0 };

	while (true) {
		if (str.empty()) break;
		if (!isspace(str[0])) break;

		str.erase(str.begin());
		chars++;
	}

	return chars;
}