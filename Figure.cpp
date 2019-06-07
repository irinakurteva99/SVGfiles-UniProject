#include "Figure.h"
#include <iostream>



void Figure::increaseX(int x)
{
	x_coordinate += x;
}

void Figure::increaseY(int y)
{
	y_coordinate += y;
}

Figure & Figure::operator=(const Figure & other)
{
	if (this != &other)
	{
		delete[] this->colour;
		copy(other);
	}
	return *this;
}

int Figure::readNumber(std::string input, std::string textToFind)
{
	const char * Point = strstr(input.c_str(), textToFind.c_str());
	Point += textToFind.length() + 1;
	std::string NumberString;
	while (*Point != '\"')
	{
		NumberString += *Point;
		Point++;
	}
	return std::stod(NumberString);
}

void Figure::copy(const Figure& other)
{
	this->x_coordinate = other.x_coordinate;
	this->y_coordinate = other.y_coordinate;
	int colourLength = strlen(other.colour);
	this->colour = new char[colourLength + 1];
	strcpy(this->colour, other.colour);
}

void Figure::print(std::ostream& os) const
{
	os << "x:" << x_coordinate << " y:" << y_coordinate << " colour:" << colour;
}

Figure::Figure()
{
	int x = 0;
	int y = 0;
	this->colour = nullptr;
}

Figure::Figure(int x, int y, const char * colour)
{
	x_coordinate = x;
	y_coordinate = y;
	int colourLength = strlen(colour);
	this->colour = new char[colourLength + 1];
	strcpy(this->colour, colour);
}

Figure::Figure(const Figure & other)
{
	copy(other);
}

Figure::~Figure()
{
	if (this->colour != nullptr) {
		delete[] this->colour;
	} 
	this->colour = nullptr;
}

std::ostream & operator<<(std::ostream & out, Figure & figure)
{
	figure.print(out);
	return out;
}
