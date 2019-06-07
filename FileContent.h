#pragma once
#include "Figure.h"
#include <iostream>
#include <string>
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include "File.h"

class FileContent : public File
{
	int array_capacity;
	int figures_count;
	//void copy(FileContent const& other);
	void destroy();
	Figure** figures;
	void copy(FileContent const& other);
public:
	FileContent();
	FileContent(std::string _fileName, std::string _headers);
	FileContent(std::string _fileName, std::string _headers, Figure** figures,int figures_count);
	FileContent(std::string _fileName, Figure** figures, int figures_count);
	FileContent(const FileContent & other);
	~FileContent();
	///prints all figures on the console
	void print();
	///prints all figures to a file or another ostream
	void filePrint(std::ostream& os);
	///prints only the coordinates of all figures, used for testing only
	void coordinatePrint();
	///adds a new figure
	bool create();
	///deletes the figure with index figurePosition
	bool erase(int figurePosition);
	///the last parameter is optional, if not added, all figures are translated, else only the figure in that position is translated
	bool translate(int x, int y, int figureIndex = -1);
	// районът - кръг или правоъгълник, е обект от тип фигура от съответния вид със съответните параметри - координати, радиус за кръга и 
	// височина и ширина за правоъгълникът
	Figure** within(Figure& region, int& counter);
	FileContent& operator=(const FileContent& other);
	
	/*Figure* figureFactory(std::string s);*/
};

