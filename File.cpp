#include "File.h"



File::File()
{
	fileName = "newFile.svg";
	headers = "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\" >";
}


File::File(std::string _fileName, std::string _headers)
{
	fileName = _fileName;
	headers = _headers;
}

File::File(std::string _fileName)
{
	fileName = _fileName;
	headers = "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\" >";
}

File::~File()
{
}
