#include "FileContent.h"
#include <iostream>

void FileContent::copy(FileContent const& other)
{
	this->array_capacity = other.array_capacity;
	this->figures_count = other.figures_count;
	this->figures = new Figure*[array_capacity];
	for (int i = 0; i < figures_count; i++)
	{
		figures[i] = other.figures[i]->clone();
	}
}

void FileContent::destroy()
{
	delete[] figures;
}

FileContent::FileContent() : File()
{
	figures = nullptr;
	array_capacity = 0;
	figures_count = 0;
}

FileContent::FileContent(std::string _fileName, std::string _headers) : File(_fileName, _headers)
{
	figures = nullptr;
	array_capacity = 0;
	figures_count = 0;
}

FileContent::FileContent(std::string _fileName, std::string _headers, Figure ** figures,int figures_count) : File(_fileName, _headers)
{
	this->figures = new Figure*[figures_count + 10];
	for (int i = 0; i < figures_count; i++)
	{
		this->figures[i] = figures[i];
	}
	this->figures_count = figures_count;
	array_capacity = figures_count + 10;
}

FileContent::FileContent(std::string _fileName, Figure ** figures, int figures_count) : File(_fileName)
{
	this->figures = new Figure*[figures_count + 10];
	for (int i = 0; i < figures_count; i++)
	{
		this->figures[i] = figures[i];
	}
	this->figures_count = figures_count;
	array_capacity = figures_count + 10;
}

FileContent::FileContent(const FileContent & other) : File(other)
{
	copy(other);
}


FileContent::~FileContent()
{
	destroy();
}


void FileContent::print()
{
	for (int i = 0; i < figures_count; i++)
	{
		std::cout << *(figures[i]);
	}
}

void FileContent::filePrint(std::ostream& os)
{
	for (int i = 0; i < figures_count; i++)
	{
		figures[i]->serialize(os);
	}
}

void FileContent::coordinatePrint()
{
	for (int i = 0; i < figures_count; i++)
	{
		std::cout << figures[i]->getTop() << figures[i]->getBottom() << figures[i]->getLeft() << figures[i]->getRight() << std::endl;
	}
}

bool FileContent::create()
{
	if (figures_count >= array_capacity)
	{
		array_capacity += 10;
		Figure** helperArray = new Figure* [array_capacity];
		for (int i = 0; i < figures_count; i++)
		{
			helperArray[i] = figures[i];
		}
		destroy();
		figures = helperArray;
	}
	std::string type;
	std::cout << "Write rectangle, circle or line: ";
	std::cin >> type;
	if (type == "circle")
	{
		int x, y, radius;
		std::string colour;
		std::cin >> x >> y >> radius;
		std::cin >> colour;
		figures[figures_count] = new Circle(x, y, radius, colour.c_str());
		figures_count++;
		return true;
	}
	if (type == "line")
	{
		int x, y, xEnd, yEnd;
		std::string colour;
		std::cin >> x >> y >> xEnd >> yEnd;
		std::cin >> colour;
		figures[figures_count] = new Line(x, y, xEnd, yEnd, colour.c_str());
		figures_count++;
		return true;
	}
	if (type == "rectangle")
	{
		int x, y, height, width;
		std::string colour;
		std::cin >> x >> y >> width >> height;
		std::cin >> colour;
		figures[figures_count] = new Rectangle(x, y, width, height, colour.c_str());
		figures_count++;
		return true;
	}
	return false;
}

bool FileContent::erase(int figurePosition)
{
	if (figurePosition >= figures_count || figurePosition < 0)
	{
		return false;
	}

	delete figures[figurePosition];
	figures_count--;
	for (int i = figurePosition; i < figures_count; i++)
	{
		figures[i] = figures[i + 1];
	}
	return true;
}

bool FileContent::translate(int x, int y, int figureIndex)
{
	if (figureIndex == -1)
	{
		int i = 0;
		for (; i < figures_count; i++)
		{
			(*(figures[i])).increaseX(x);
			(*(figures[i])).increaseY(y);
		}
		return i == figures_count;
	}
	if (figureIndex >= figures_count || figureIndex < -1)
	{
		return false;
	}
	(*(figures[figureIndex])).increaseX(x);
	(*(figures[figureIndex])).increaseY(y);
	return true;
}

Figure ** FileContent::within(Figure & region, int& counter)
{
	int array_size = 10;
	Figure** figuresWithinContainer = new Figure*[array_size];
	for (int i = 0; i < figures_count; i++)
	{
		if (region.isAFigureWithin(figures[i]))
		{
			if (counter < array_size)
			{
				figuresWithinContainer[counter] = figures[i];
			}
			else
			{
				Figure** figuresWithinContainerHelper = new Figure*[array_size + 10];
				array_size += 10;
				for (int j = 0; j < counter; j++)
				{
					figuresWithinContainerHelper[j] = figuresWithinContainer[j];
				}
				delete[] figuresWithinContainer;
				figuresWithinContainerHelper[counter] = figures[i];
				figuresWithinContainer = figuresWithinContainerHelper;
			}

			counter++;
		}
	}

	if (counter == 0)
	{
		delete[] figuresWithinContainer;
		return nullptr;
	}
	
	return figuresWithinContainer;
}

FileContent & FileContent::operator=(const FileContent & other)
{
	if (this != &other)
	{
		delete[] figures;
		copy(other);
	}
	return *this;
}

/*Figure * FileContent::figureFactory(std::string s)
{
	if (s == "circle")
	{
		return new Circle();
	}
	if (s == "line")
	{
		return new Line();
	}
	if (s == "rectanglie")
	{
		return new Rectangle();
	}
	return nullptr;
}*/
