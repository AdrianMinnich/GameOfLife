#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::experimental::filesystem;

class PatternEncoder
{
public:
	fs::path filePath;
	std::string info;
	std::string name;
	int width, height;
	std::string RLE_format;
	std::vector<std::vector<bool>> cellPattern;

	PatternEncoder();
	PatternEncoder(fs::path filePath);
	~PatternEncoder();

	void setFilePath(fs::path filePath);
	void readData(fs::path filePath);
	void parseData(std::string s);
	void fillCellPattern();
};

