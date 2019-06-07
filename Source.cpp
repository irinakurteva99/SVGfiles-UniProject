#include <iostream>
#include "Figure.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include "FileContent.h"
#include <fstream>
#include "File.h"
#include <sstream>

using namespace std;

void testFigurePrint() {
	Figure* figure;
	char* colour = new char[50];
	char colourBlue[5] = "Blue";
	strcpy(colour, colourBlue);
	Line line(5, 5, 10, 10, colour);
	figure = &line;
	std::cout << line << endl;
	std::cout << *figure << endl;
	char colourRed[4] = "Red";
	strcpy(colour, colourRed);
	Circle circle(0, 2, 5, colour);
	figure = &circle;
	std::cout << circle << endl;
	std::cout << *figure << endl;
	char colourYellow[7] = "Yellow";
	strcpy(colour, colourYellow);
	Rectangle rectangle(0, 2, 8, 5, colour);
	figure = &rectangle;
	std::cout << rectangle << endl;
	std::cout << *figure << endl;
}

void testFigureArrayCreation() {
	Figure** figuresPointersArray = new Figure*[3];
	char* colour = new char[50];
	char colourBlue[5] = "Blue";
	strcpy(colour, colourBlue);
	Circle* circle = new Circle(0, 2, 5, colour);
	Line* line = new Line(5, 5, 10, 10, colour);
	Rectangle* rectangle = new Rectangle(0, 2, 8, 5, colour);
	figuresPointersArray[0] = circle;
	figuresPointersArray[1] = line;
	figuresPointersArray[2] = rectangle;
	FileContent testFile("TestFile", figuresPointersArray, 3);
	testFile.print();
}

void testFigureTranslate() {
	Figure** figuresPointersArray = new Figure*[3];
	char* colour = new char[50];
	char colourBlue[5] = "Blue";
	strcpy(colour, colourBlue);
	Circle* circle = new Circle(0, 2, 5, colour);
	Line* line = new Line(5, 5, 10, 10, colour);
	Rectangle* rectangle = new Rectangle(0, 2, 8, 5, colour);
	figuresPointersArray[0] = circle;
	figuresPointersArray[1] = line;
	figuresPointersArray[2] = rectangle;
	FileContent testFile("TestFile", figuresPointersArray, 3);
	testFile.print();
	testFile.translate(10, 5, 1);
	testFile.print();
}

void testCoordinates() {
	Figure** figuresPointersArray = new Figure*[3];
	char* colour = new char[50];
	char colourBlue[5] = "Blue";
	strcpy(colour, colourBlue);
	Circle* circle = new Circle(0, 2, 5, colour);
	Line* line = new Line(5, 5, 10, 10, colour);
	Rectangle* rectangle = new Rectangle(0, 2, 8, 5, colour);
	figuresPointersArray[0] = circle;
	figuresPointersArray[1] = line;
	figuresPointersArray[2] = rectangle;
	FileContent testFile("TestFile", figuresPointersArray, 3);
	testFile.coordinatePrint();
}

void testFileContentCopy() {
	Figure** figuresPointersArray = new Figure*[3];
	char* colour = new char[50];
	char colourBlue[5] = "Blue";
	strcpy(colour, colourBlue);
	Circle* circle = new Circle(0, 2, 5, colour);
	Line* line = new Line(5, 5, 10, 10, colour);
	Rectangle* rectangle = new Rectangle(0, 2, 8, 5, colour);
	figuresPointersArray[0] = circle;
	figuresPointersArray[1] = line;
	figuresPointersArray[2] = rectangle;
	FileContent testFile("TestFile", figuresPointersArray, 3);
	FileContent newFile(testFile);
	newFile.print();
	testFile.print();
	newFile.translate(10, 10);
	newFile.print();
	testFile = newFile;
	testFile.print();
}

void testFiles() {
	string fileName = "test.svg";
	ifstream in(fileName);
	string headers;
	string input;
	while (getline(in, input) && input != "<svg>") {
		headers += input;
		headers += '\n';
	}
	string figures;
	while (getline(in, input) && input != "</svg>") {
		figures += input;
		figures += '\n';
	}
	in.close();
	std::cout << headers << endl;
	std::cout << figures << endl;
	
	/*File nfile;
	string text = nfile.getHeader();
	cout << text << endl;*/

	File currentFile(fileName, headers);
	std::cout << currentFile.getHeader() << endl << currentFile.getName() << endl;
	ofstream out("test.svg", ios::trunc);
	out << headers << "<svg>" << endl << figures << "</svg>";

}

void translateFigures(FileContent& fileC) {
	std::cout << "one or all?" << endl;
	//cout << "Translation vertical, horisontal and figure index(optional):" << endl;
	string count;
	cin >> count;
	int x, y;
	int arrayIndex = -1;
	if (count == "one") {
		cin >> x >> y >> arrayIndex;
	}
	else {
		cin >> x >> y;
	}
	if (fileC.translate(x, y, arrayIndex)) {
		std::cout << endl << "Successfully translated" << endl;
	}
	else {
		std::cout << endl << "Error during translation" << endl;
	}
}

void addFigure(FileContent& fileC) {
	if (fileC.create()) {
		std::cout << endl << "Successfull created a figure" << endl;
	}
	else {
		std::cout << endl << "Error during creation of a figure" << endl;
	}
}

void eraseFigure(FileContent& fileC) {
	int figureIndex;
	cin >> figureIndex;
	if (fileC.erase(figureIndex)) {
		std::cout << endl << "Successfully erased" << endl;
	}
	else {
		std::cout << endl << "Error during erase" << endl;
	}
}

void withinFigure(FileContent& currentFile) {
	std::cout << "circle or rectangle?" << endl;
	string shape;
	std::cin >> shape;
	int counter = 0;
	if (shape == "rectangle")
	{
		int x, y, width, height;
		std::cin >> x >> y >> width >> height;
		Rectangle rectangle(x, y, width, height, "");
		Figure& shapeToSearch = rectangle;
		Figure** figuresWithin = currentFile.within(shapeToSearch, counter);
		if (figuresWithin == nullptr) {
			std::cout << "No shapes in that region" << endl;
		}
		else
		{
			for (int i = 0; i < counter; i++)
			{
				std::cout << endl << *(figuresWithin[i]);
			}
		}
		delete[] figuresWithin;
	}
	else if (shape == "circle")
	{
		int x, y, radius;
		cin >> x >> y >> radius;
		Circle circle(x, y, radius, "");
		Figure& shapeToSearch = circle;
		Figure** figuresWithin = currentFile.within(shapeToSearch, counter);
		if (figuresWithin == nullptr) {
			std::cout << "No shapes in that region" << endl;
		}
		else
		{
			for (int i = 0; i < counter; i++)
			{
				std::cout << endl << *(figuresWithin[i]);
			}
		}
		delete[] figuresWithin;
	}
	else
	{
		std::cout << "Invalid shape" << endl;
	}
}

void save(string fileName, FileContent& fileC) {
	ofstream file(fileName, ios::trunc);
	file << fileC.getHeader();
	file << "<svg>" << endl;
	fileC.filePrint(file);
	file << "</svg>";
	if (file)
	{
		cout << "Successfully saved" << endl;
	}
	else
	{
		cout << "Error during saving" << endl;
	}
}

void userInterfaceFile(FileContent& currentFile) {
	string command;
	std::cout << "Hello" << endl;
	std::cout << "If you want to see all commands, write help" << endl;
	do
	{
		std::cout << endl;
		cin >> command;
		std::cout << endl;
		if (command == "translate")
		{
			translateFigures(currentFile);
		}
		else if (command == "add")
		{
			//cout << "Add: " << endl;
			addFigure(currentFile);
		}
		else if (command == "erase")
		{
			//cout << "Erase: " << endl;
			eraseFigure(currentFile);
		}
		else if (command == "print")
		{
			currentFile.print();
		}
		else if (command == "help")
		{
			std::cout << "If you want to translate a figure, write traslate" << endl;
			std::cout << "If you want to add a figure, write add" << endl;
			std::cout << "If you want to erase a figure, write erase" << endl;
			std::cout << "If you want to print all figures, write print" << endl;
			std::cout << "If you want to check whether a figure is within a certain region, write within" << endl;
			std::cout << "To close the current file, write close" << endl;
		}
		else if (command == "within") {
			//std::cout << "Within: " << endl;
			withinFigure(currentFile);
		}
		else if (command == "save")
		{
			save(currentFile.getName(), currentFile);
		}
		else if (command == "saveAs")
		{
			string fileToSave;
			cin >> fileToSave;
			save(fileToSave, currentFile);
		}
		std::cout << endl;
	} while (command != "close");
}

void userInterface() {
	string command;
	cout << "Please input a command" << endl;
	cin >> command;
	while (command != "exit") {
		if (command == "open") {
			//отваря се файл и съдържанието му се зарежда във FileContent currentFile;
			string fileName;
			cin >> fileName;
			if (strstr(fileName.c_str(), ".svg") == nullptr)
			{
				std::cout << "Invalid File" << endl;
				return;
			}
			fstream in(fileName);
			string headers = "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\" >";
			string input;
			string figures;
			int figuresCounter = 0;
			if (in.is_open()) {
				headers = "";
				while (getline(in, input) && input != "<svg>") {
					headers += input;
					headers += '\n';
				}
				while (getline(in, input) && input != "</svg>") {
					figures += input;
					figures += '\n';
					figuresCounter++;
				}
				in.close();
			}
			else {
				ofstream out(fileName);
				out.close();
			}

			stringstream figuresStream(figures);

			Figure** figuresPointersArray = new Figure*[figuresCounter];
			int currentFigIndex = 0;
			while (getline(figuresStream, input)) {
				if (strstr(input.c_str(), "rect") != nullptr) {
					Rectangle* currentFigure = new Rectangle();
					currentFigure->read(input);
					figuresPointersArray[currentFigIndex] = currentFigure;
					currentFigIndex++;
				}
				else if (strstr(input.c_str(), "circle") != nullptr) {
					Circle* currentFigure = new Circle();
					currentFigure->read(input);
					figuresPointersArray[currentFigIndex] = currentFigure;
					currentFigIndex++;
				}
				else if (strstr(input.c_str(), "line") != nullptr) {
					Line* currentFigure = new Line();
					currentFigure->read(input);
					figuresPointersArray[currentFigIndex] = currentFigure;
					currentFigIndex++;
				}
			}
			FileContent currentFile(fileName, headers, figuresPointersArray, currentFigIndex);
			userInterfaceFile(currentFile);
		}
		else
		{
			cout << "Invalid operation" << endl;
		}
		cout << "Please input a command" << endl;
		cin >> command;
	}
	
	std::cout << "Bye" << endl;
}

int main() {
	//testFigurePrint();
	//testFigureArrayCreation();
	//testFigureTranslate();
	//testCoordinates();
	//testFileContentCopy();
	userInterface();
	//testFiles();
	return 0;
}