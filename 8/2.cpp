#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

std::vector<std::string> readFileLines(const std::string& filePath);
size_t readSizeT(std::string& str);

struct Position {
	int x, y, z;

	float distance(const Position& other) const {
		const size_t dx { static_cast<size_t>(other.x - x) };
		const size_t dy { static_cast<size_t>(other.y - y) };
		const size_t dz { static_cast<size_t>(other.z - z) };
		return std::sqrtf(dx*dx + dy*dy + dz*dz);
	}
};

struct Distance {
	float dist;
	int pos1I, pos2I;

	bool operator<(const Distance& other) const {
		return dist < other.dist;
	}
};

class Group {
public:

	bool contains(int i) const {
		for (const int& member : _memberIndexes) {
			if (member == i) return true;
		}
		return false;
	}

	void add(int i) {
		_memberIndexes.push_back(i);
	}

	void addGroup(const Group& other) {
		for (const int& member : other._memberIndexes) {
			_memberIndexes.push_back(member);
		}
	}

	size_t size(void) const {
		return _memberIndexes.size();
	}

private:

	std::vector<int> _memberIndexes {};
};

int main(int argc, char* argv[]) {
	if (argc != 2) throw std::runtime_error("Expected 1 command line argument");

	std::vector<std::string> lines { readFileLines(argv[1]) };
	if (lines.size() == 0) throw std::runtime_error("Bad input file - file was empty");

	std::vector<Position> positions {};

	for (std::string& line : lines) {
		const int x { static_cast<int>(readSizeT(line)) };

		if (line.empty()) throw std::runtime_error("Bad input file - lines must contain 3 numbers");
		if (line[0] != ',') throw std::runtime_error("Bad input file - numbers must be separated by ','");
		line.erase(line.begin());

		const int y { static_cast<int>(readSizeT(line)) };

		if (line.empty()) throw std::runtime_error("Bad input file - line must contain 3 numbers");
		if (line[0] != ',') throw std::runtime_error("Bad input file - numbers must be separated by ','");
		line.erase(line.begin());

		const int z { static_cast<int>(readSizeT(line)) };

		if (!line.empty()) throw std::runtime_error("Bad input file - lines must be empty past the 3rd number");

		positions.push_back({ x, y, z });
	}

	std::vector<Distance> distances {};

	for (int i = 0; i < static_cast<int>(positions.size()); i++) {
		for (int j = i + 1; j < static_cast<int>(positions.size()); j++) {
			distances.push_back({ positions[i].distance(positions[j]), i, j });
		}
	}

	std::sort(distances.begin(), distances.end() - 1);

	std::vector<Group> groups {};

	for (int i = 0; i < static_cast<int>(positions.size()); i++) {
		groups.emplace_back();
		groups.back().add(i);
	}

	int i { 0 };
	while (groups.size() > 1) {
		const int pos1I = distances[i].pos1I;
		const int pos2I = distances[i].pos2I;

		bool found { false };

		for (Group& group : groups) {
			if (group.contains(pos1I)) {
				found = true;

				if (!group.contains(pos2I)) {
					bool otherFound { false };

					for (int j = 0; j < static_cast<int>(groups.size()); j++) {
						if (groups[j].contains(pos2I)) {
							assert(!groups[j].contains(pos1I));
							otherFound = true;

							group.addGroup(groups[j]);

							groups.erase(groups.begin() + j);
							break;
						}
					}

					assert(otherFound);
				}

				break;
			}
		}

		assert(found);

		if (groups.size() == 1) {
			std::cout << static_cast<size_t>(positions[pos1I].x) * static_cast<size_t>(positions[pos2I].x) << std::endl;
		}

		i++;
	}

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