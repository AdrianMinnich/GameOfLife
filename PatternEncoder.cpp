#include "pch.h"
#include "PatternEncoder.h"



PatternEncoder::PatternEncoder()
{
	
}

PatternEncoder::PatternEncoder(fs::path filePath)
{
	readData(filePath);
	parseData(info);
	cellPattern.resize(width, std::vector<bool>(height, false));
	fillCellPattern();
}

PatternEncoder::~PatternEncoder()
{
}

void PatternEncoder::setFilePath(fs::path filePath)
{
	this->filePath = filePath;
	readData(filePath);
	parseData(info);
	cellPattern.resize(width);
	for (auto i = 0; i < width; i++) {
		cellPattern[i].resize(height);
	}
	for (auto x = 0; x < width; x++) {
		for (auto y = 0; y < height; y++) {
			cellPattern[x][y] = false;
		}
	}
	fillCellPattern();
}

void PatternEncoder::readData(fs::path filePath)
{
	if (fs::exists(filePath)) {
		std::ifstream f{ filePath };
		const auto fsize = fs::file_size(filePath);
		std::string buffer(fsize, ' ');
		f.read((char*)buffer.data(), fsize);
		info = buffer;
	}
}

void PatternEncoder::parseData(std::string s)
{
	auto separator = s.find("#N");
	name = s.substr(separator + 3, s.find("\n") - 3);

	separator = s.find("x = ");
	width = std::stoi(s.substr(separator + 4, s.find(", y") - 1));

	separator = s.find("y = ");
	height = std::stoi(s.substr(separator + 4, s.find(", rule") - 1));

	separator = s.find("\n", separator);
	RLE_format = s.substr(separator + 1, s.find("!"));

	std::cout << name << " " << width << " " << height << " " << RLE_format << std::endl;
}

void PatternEncoder::fillCellPattern()
{
	int x = 0;
	int y = 0;
	int number = 0;
	bool alive = false;

	for (auto it = RLE_format.begin(); it != RLE_format.end(); it++) {
		
		if (*it == '!')
			break;
		else if (isdigit(*it))
			number = number * 10 + ((int)*it - '0');
		else {
			if (*it == 'b' || *it == 'o') { // b - dead, o - alive
				*it == 'b' ? alive = false : alive = true;

				if (number == 0) 
					number = 1;
				for (auto i = 0; i < number; i++)
					cellPattern[x + i][y] = alive; // ?????? good

				x += number;
				number = 0;
			}
			else if (*it == '$') {
				x = 0;
				number != 0 ? y += number : y++;
				number = 0;
			}
		}
	}
}
