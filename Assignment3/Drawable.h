#pragma once
#include "Drawing.h" // Includes the Drawing.h header file.
#include <vector> // includes the vector library.
using namespace std; // Using the standard library.

class DrawObject // Class of name DrawObject. 
{
private:
	COLOUR colour; // Private COLOUR data type in the class with the name colour.
protected:
	vector<COORD> coordVector; // Protected vector that holds COORDs with the name coordVector.
public:
	DrawObject(COLOUR inputColour) { colour = inputColour; } // DrawObject constructor that accepts a COLOUR and then sets data member colour to the input colour.
	COLOUR getColour() { return colour; } // Getter function to obtain the data meber colour.
	virtual void draw(Drawing &refDrawing) = 0; // Abstract funtion declaration.
	virtual ~DrawObject() {} // Destructor for the DrawObject class.
};

class Point : public DrawObject // Class of name Point that inherits from DrawObject.
{
public:
	Point(COLOUR pColour, COORD pCoord) :DrawObject(pColour) { coordVector.push_back(pCoord); } // Contructor that takes in a COLOUR and COORD and sets the colour variable
																								// as the pColour parameter by way of an initialization list. Also a COORD
																								// is added to the vector that carries COORDs.
	virtual void draw(Drawing &refDrawing) { refDrawing.setPixel(coordVector.at(0), getColour()); } // Defines the abstract function. Based on the COLOUR and COORD a pixel is set
																									// on the drawing.
	~Point() {} // Destructor for the Point class.
};

class Line : public DrawObject // Class of name Line that inherits from DrawObject.
{
public:
	Line(COLOUR lColour, COORD l1Coord, COORD l2Coord) :DrawObject(lColour)  // Constructor that takes in 2 COORDs and 1 COLOUR and sets the colour variable as the lColour by way of
	{																		 // an initilization list. Also both COORDs are added to the vectore that carries COORDs.
		coordVector.push_back(l1Coord); 
		coordVector.push_back(l2Coord);
	}
	virtual void draw(Drawing &refDrawing) { refDrawing.drawLine(coordVector.at(0), coordVector.at(1), getColour()); } // Defines the abstract function. Based on the COLOUR and COORDs a line
																													   // is drawn on the drawing.
	~Line() {} // Destructor for the Line class.
};

class Shape : public DrawObject // Class of name Shape that inherits from DrawObject.
{
private:
	static int shapes; // Declares the static int that hold the number of shapes that there currently are.
public:
	Shape(COLOUR sColour) :DrawObject(sColour) { shapes++; } // Constructor that takes in 1 COLOUR and sets the colour variable as the sColour by way of an initialization list. Also adds 1 to the shapes variable.
	virtual void draw(Drawing &refDrawing) // Defines the abstract function. 		
	{
		int i = 0; // variable declared and initialized as 1.
		for (i; i < coordVector.size() - 1; i++) // for look to draw lines that will eventually create a shape.
		{
			refDrawing.drawLine(coordVector.at(i), coordVector.at(i + 1), getColour()); // Lines draws with the given colour.
		}
		refDrawing.drawLine(coordVector.at(0), coordVector.at(i), getColour()); // Connects the first point to the last point to complete the shape.
	}
	void addCoord(COORD newCoord) { coordVector.push_back(newCoord); } // Function to add a new coordiate to the vector that carries COORDs.
	static int getNumShapes() { return shapes; } // Getter function that returns the number of shapes.
	~Shape() { shapes--; } // Destructor that decrements the shape by 1.
};

int Shape::shapes = 0; // Initilaizes the static int.