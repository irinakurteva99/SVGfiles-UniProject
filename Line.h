#pragma once
#include "Figure.h"
#include <iostream>
#include <string>

class Line : public Figure
{
	int x_coordinate_end;
	int y_coordinate_end;
	void print(std::ostream& os = std::cout) const;
public:
	Line();
	Line(int x, int y, int xEnd, int yEnd, const char* colour);
	~Line();
	void increaseX(int x);
	void increaseY(int y);
	///returns the coordinates of the ends of the line
	std::vector<std::pair<int, int>> getCoordiantes();
	int getTop();
	int getBottom();
	int getLeft();
	int getRight();
	Line* clone() const;
	///within does not work with lines, the function is vitual though, in case other figures like hexagone are to be added
	bool isAFigureWithin(Figure* other);
	void serialize(std::ostream& out) const;
	void read(std::string input);
};

