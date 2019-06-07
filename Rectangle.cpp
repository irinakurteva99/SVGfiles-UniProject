#include "Rectangle.h"
#include <iostream>


void Rectangle::print(std::ostream& os) const
{
	os << "rectangle width:" << width << " height:" << height << ' ';
	Figure::print();
	os << std::endl;
}

Rectangle::Rectangle() : Figure()
{
	width = 0;
	height = 0;
}

Rectangle::Rectangle(int x, int y, int width, int height, const char* colour) : Figure(x, y, colour)
{
	this->width = width;
	this->height = height;
}


Rectangle::~Rectangle()
{
}

std::vector<std::pair<int, int>> Rectangle::getCoordiantes()
{
	std::vector<std::pair<int, int>> coordinates;
	coordinates.push_back(std::pair<int, int>(x_coordinate, y_coordinate));
	coordinates.push_back(std::pair<int, int>(x_coordinate, y_coordinate + height));
	coordinates.push_back(std::pair<int, int>(x_coordinate + width, y_coordinate));
	coordinates.push_back(std::pair<int, int>(x_coordinate + width, y_coordinate + height));
	return coordinates;
}

int Rectangle::getTop()
{
	return y_coordinate + height;
}

int Rectangle::getBottom()
{
	return y_coordinate;
}

int Rectangle::getLeft()
{
	return x_coordinate;
}

int Rectangle::getRight()
{
	return x_coordinate + width;
}

Rectangle * Rectangle::clone() const
{
	return new Rectangle(*this);
}

bool Rectangle::isAFigureWithin(Figure * other)
{
	int regionTop = this->getTop();
	int regionLeft = this->getLeft();
	int regionBottom = this->getBottom();
	int regionRight = this->getRight();
	std::vector<std::pair<int, int>> otherCoords = other->getCoordiantes();
	for (int i = 0; i < otherCoords.size(); i++)
	{
		int x_point = std::get<0>(otherCoords.at(i));
		int y_point = std::get<1>(otherCoords.at(i));
		if (regionTop < y_point || regionLeft > x_point ||
			regionBottom > y_point || regionRight < x_point)
		{
			return false;
		}
	}
	return true;
}

void Rectangle::serialize(std::ostream & out) const
{
	out << "<rect x=\"" << x_coordinate << "\" y=\"" << y_coordinate << "\" width=\"" << width << "\" height=\"" << height << "\" fill=\"" << colour << "\" />" << std::endl;
}

void Rectangle::read(std::string input)
{
	int xCoord = readNumber(input, "x=");
	int yCoord = readNumber(input, "y=");
	int width = readNumber(input, "width=");
	int height = readNumber(input, "height=");
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
	this->width = width;
	this->height = height;
	this->colour = new char[colour.length() + 1];
	strcpy(this->colour, colour.c_str());
}


