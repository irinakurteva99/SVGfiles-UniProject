#pragma once
#include <string>
class File
{
	std::string headers;
	std::string fileName;
public:
	File();
	File(std::string _fileName, std::string _headers);
	File(std::string _fileName);
	virtual ~File();
	std::string getHeader() { return headers; }
	std::string getName() { return fileName; }
};
