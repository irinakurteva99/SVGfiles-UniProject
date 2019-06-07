#include "Line.h"
#include <iostream>


void Line::print(std::ostream& os) const
{
	os << "line x_end:" << x_coordinate_end << ' ' << "y_end:" << y_coordinate_end << ' ';
	Figure::print();
	os << std::endl;
}

Line::Line() : Figure()
{
	this->x_coordinate_end = 0;
	this->y_coordinate_end = 0;
}

Line::Line(int x, int y, int xEnd, int yEnd, const char* colour): Figure(x, y, colour)
{
	this->x_coordinate_end = xEnd;
	this->y_coordinate_end = yEnd;
}


Line::~Line()
{
}

void Line::increaseX(int x)
{
	x_coordinate += x;
	x_coordinate_end += x;
}

void Line::increaseY(int y)
{
	y_coordinate += y;
	y_coordinate_end += y;
}

std::vector<std::pair<int, int>> Line::getCoordiantes()
{
	std::vector<std::pair<int, int>> coordinates;
	coordinates.push_back(std::pair<int, int>(x_coordinate, y_coordinate));
	coordinates.push_back(std::pair<int, int>(x_coordinate_end, y_coordinate_end));
	return coordinates;
}

int Line::getTop()
{
	return y_coordinate;
}

int Line::getBottom()
{
	return y_coordinate;
}

int Line::getLeft()
{
	return x_coordinate;
}

int Line::getRight()
{
	return x_coordinate;
}

Line * Line::clone() const
{
	return new Line(*this);
}

bool Line::isAFigureWithin(Figure * other)
{
	return false;
}

void Line::serialize(std::ostream & out) const
{
	out << "<line x1=\"" << x_coordinate << "\" y1=\"" << y_coordinate << "\" x2=\"" << x_coordinate_end << "\" y2=\"" << y_coordinate_end << "\" fill=\"" << colour << "\" />" << std::endl;
}

void Line::read(std::string input)
{
	int xCoord = readNumber(input, "x1=");
	int yCoord = readNumber(input, "y1=");
	int xCoordE = readNumber(input, "x2=");
	int yCoordE = readNumber(input, "y2=");
	const char * colourP = strstr(input.c_str(), "fill=");
	colourP += 6;
	std::string colour;
	while (*colourP != '\"')
	{
		colour += *colourP;
		colourP++;
	}
	this->x_coordinate = xCoord;
	this->y_coordinate = yCoord;
	this->x_coordinate_end = xCoordE;
	this->y_coordinate_end = yCoordE;
	this->colour = new char[colour.length() + 1];
	strcpy(this->colour, colour.c_str());
}
