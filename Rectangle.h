#pragma once
#include "Figure.h"
#include <iostream>
#include <string>

class Rectangle : public Figure
{
	int width;
	int height;
	void print(std::ostream& os = std::cout) const;
public:
	Rectangle();
	Rectangle(int x, int y, int width, int height, const char* colour);
	~Rectangle();
	///returns the coordinates of the edges of the rectangle
	std::vector<std::pair<int, int>> getCoordiantes();
	int getTop();
	int getBottom();
	int getLeft();
	int getRight();
	Rectangle* clone() const;
	///Checks whether the other figure is within the current one
	bool isAFigureWithin(Figure* other);
	void serialize(std::ostream& out) const;
	void read(std::string input);
};

