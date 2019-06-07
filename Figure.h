#pragma once
#include <iostream>
#include <vector>
#include <string>

class Figure
{
	void copy(const Figure& other);
protected:
	virtual void print(std::ostream& os = std::cout) const = 0;
	char* colour;
	int x_coordinate;
	int y_coordinate;
public:
	virtual Figure* clone() const = 0;
	Figure();
	Figure(int x, int y, const char* colour);
	Figure(const Figure& other);
	virtual ~Figure();
	friend std::ostream& operator << (std::ostream& out, Figure& figure);
	virtual void increaseX(int x);
	virtual void increaseY(int y);
	///returns the edge coordinates of the figure
	virtual std::vector<std::pair<int, int>> getCoordiantes() = 0;
	virtual int getTop() = 0;
	virtual int getBottom() = 0;
	virtual int getLeft() = 0;
	virtual int getRight() = 0;
	Figure& operator=(const Figure& other);
	///Checks whether the other figure is within the current one
	virtual bool isAFigureWithin(Figure* other) = 0;
	virtual void serialize(std::ostream& out) const = 0;
	virtual void read(std::string input) = 0;
	///Finds some number in the figure tag, for example coordinate or size
	int readNumber(std::string input, std::string textToFind);
};

std::ostream& operator << (std::ostream& out, Figure& figure);