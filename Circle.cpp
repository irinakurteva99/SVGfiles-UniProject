#include "Circle.h"
#include <iostream>
#include <cmath>


void Circle::print(std::ostream& os) const
{
	os << "circle radius:" << radius << ' ';
	Figure::print();
	os << std::endl;
}

Circle::Circle() : Figure()
{
	radius = 0;
}

Circle::Circle(int x, int y, int radius, const char * colour) : Figure(x, y, colour)
{
	this->radius = radius;
}


Circle::~Circle()
{
}

std::vector<std::pair<int, int>> Circle::getCoordiantes()
{
	std::vector<std::pair<int, int>> coordinates;
	//най-лявата, най-дясната, най-горната и най-долната точка на кръга
	coordinates.push_back(std::pair<int, int>(x_coordinate - radius, y_coordinate));
	coordinates.push_back(std::pair<int, int>(x_coordinate, y_coordinate + radius));
	coordinates.push_back(std::pair<int, int>(x_coordinate + radius, y_coordinate));
	coordinates.push_back(std::pair<int, int>(x_coordinate, y_coordinate - radius));
	//добавят се още точки за по-голяма точност при пресмятането, кръгът е приближен до многоъгълник
	coordinates.push_back(std::pair<int, int>(x_coordinate * sin(45 * PI/180), y_coordinate * cos(45 * PI / 180)));
	coordinates.push_back(std::pair<int, int>(x_coordinate * sin(-45 * PI / 180), y_coordinate * cos(-45 * PI / 180)));	
	coordinates.push_back(std::pair<int, int>(x_coordinate * sin(135 * PI / 180), y_coordinate * cos(135 * PI / 180)));	
	coordinates.push_back(std::pair<int, int>(x_coordinate * sin(-135 * PI / 180), y_coordinate * cos(-135 * PI / 180)));
	return coordinates;
}

int Circle::getTop()
{
	return y_coordinate + radius;
}

int Circle::getBottom()
{
	return y_coordinate - radius;
}

int Circle::getLeft()
{
	return x_coordinate - radius;
}

int Circle::getRight()
{
	return x_coordinate + radius;
}

Circle * Circle::clone() const
{
	return new Circle(*this);
}

bool Circle::isAFigureWithin(Figure * other)
{	
	std::vector<std::pair<int, int>> otherCoords = other->getCoordiantes();
	for (int i = 0; i < otherCoords.size(); i++)
	{
		int x_point = std::get<0>(otherCoords.at(i));
		int y_point =std::get<1>(otherCoords.at(i));
		if (pow((x_point - this->x_coordinate), 2) + pow((y_point - this->y_coordinate), 2) > (this->radius * this->radius))
		{
			return false;
		}
	}
	return true;
}

void Circle::serialize(std::ostream & out) const
{
	out << "<circle cx=\"" << x_coordinate << "\" cy=\"" << y_coordinate << "\" r=\"" << radius << "\" fill=\"" << colour << "\" />" << std::endl;
}

void Circle::read(std::string input)
{
	int xCoord = readNumber(input, "cx=");
	int yCoord = readNumber(input, "cy=");
	int radius = readNumber(input, "r=");
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
	this->radius = radius;
	this->colour = new char[colour.length() + 1];
	strcpy(this->colour, colour.c_str());
}

