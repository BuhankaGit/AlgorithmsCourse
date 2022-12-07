#include "CsvReader.h"

bool CsvReader::read(std::string filepath)
{
	std::string line;
	std::ifstream in(filepath);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			std::vector<std::string> temp = split(line, ":");
			params.push_back(RowData(temp[0], temp[1]));
		}
	}
	in.close();
	return params.size() > 0 ? true : false;
}
