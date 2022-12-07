#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <regex>

class CsvReader
{
private:
	class RowData {
	private:
		std::string name;
		std::string value;
	public:
		RowData(std::string name, std::string value) {
			this->name = name;
			this->value = value;
		};
		std::string getName() { return name; };
		std::string getValue() { return value; };
	};
	std::vector<RowData> params;
public:
	bool read(std::string filepath);
	std::vector<std::string> split(std::string arg, std::string delimiter) {
		const auto r = std::regex(delimiter.data());
		return std::vector<std::string>{
			std::sregex_token_iterator(arg.begin(), arg.end(), r, -1),
			std::sregex_token_iterator()
		};
	}
	std::vector<RowData> getParams() { return params; };
};

