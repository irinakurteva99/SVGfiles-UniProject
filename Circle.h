#pragma once
#include "Figure.h"
#include <iostream>
#include <cmath>
#include <string>

const double PI = 3.141592653589793238463;

class Circle : public Figure
{
	int radius;
	void print(std::ostream& os = std::cout) const;
public:
	Circle();
	Circle(int x, int y, int radius, const char* colour);
	~Circle();
	///returns many points which are on the circle outline, circle is treated like a polygon with lots of edges
	std::vector<std::pair<int, int>> getCoordiantes();
	int getTop();
	int getBottom();
	int getLeft();
	int getRight();
	Circle* clone() const;
	///Checks whether the other figure is within the current one
	bool isAFigureWithin(Figure* other);
	void serialize(std::ostream& out) const;
	void read(std::string input);
};

