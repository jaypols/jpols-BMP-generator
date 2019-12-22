#include <iostream> // Provides basic input and output services.
#include "Drawing.h" // Includes the Drawing header file.
#include "Drawable.h" // Includes the Drawable header file.
#include <string> // Includes the String library.
#include <forward_list> // Includes the forward list library.
using namespace std; // Utilizes the standard library.

COLOUR getColour(char *red, char *green, char *blue); // Prototype for the getColour function that is used throughout the main function.
COORD getCoordinate(char *row, char *column); // Prototype for the getCoordinate function that is used throughout the main function.

// THIS PROGRAM IS RAN FROM THE COMMAND PROMPT

int main(int argc, char* argv[]) // Main function
{
	// Creates a drawing based on the inputs of the width, height and colours that were input by the user. 
	Drawing drawing = Drawing((unsigned)atoi(argv[2]), (unsigned)atoi(argv[3]), getColour(argv[4], argv[5], argv[6]));

	static int x = 7; // Declares a static that keeps track of the current argv argument that is being utilized. Initialized to 7 since the first 6 arguments have already been used.
	forward_list<DrawObject*> drawObjects; // Creates a forward list that hold DrawObject pointers.

	for (x; x < argc; x++) // For loop that continues until there are no more arguments that were entered.
	{

		if (*argv[x] == 'L' || *argv[x] == 'l') // if the argument is L or l is entered then a new DrawObject is added to the forward list using the arguments entered by the user.
		{
			drawObjects.push_front(new Line(getColour(argv[x + 1], argv[x + 2], argv[x + 3]), getCoordinate(argv[x + 4], argv[x + 5]), getCoordinate(argv[x + 6], argv[x + 7])));
			x += 7; // Skips all the arguments that were prevalent to the Line.
		}

		else if (*argv[x] == 'P' || *argv[x] == 'p') // If the argument is P or p is entered then a new DrawObjects is added to the forward list using the arguments entered by the user.
		{
			drawObjects.push_front(new Point(getColour(argv[x + 1], argv[x + 2], argv[x + 3]), getCoordinate(argv[x + 4], argv[x + 5])));
			x += 5; // Skips all the arguments that were prevalent to the Point.
		}

		else if (*argv[x] == 'S' || *argv[x] == 's') // If the argument is S or s is entered then a new DrawObject is added to the forward list using the arguments entered by the user.
		{
			Shape *nShape = new Shape(getColour(argv[x + 1], argv[x + 2], argv[x + 3])); // a new shape based on the COLOUR entered is created.
			for (int i = 0; i < atoi(argv[x + 4]); i++) // This adds all the coordinates for the lines that the user entered.
			{
				nShape->addCoord(getCoordinate(argv[x + 5 + 2*i], argv[x + 6 + 2*i])); // Coordinate added.
			}
			drawObjects.push_front(nShape); // the Object is then added to the forward list.
			x = x + 4 + (2 * (atoi(argv[x + 4]))); // Skips all the arguments that were prevalent to the Shape.
		}

		else // If none of those values are entered then it continues on with the loop.
		{
			continue;
		}

	}

	cout << "Number of Shapes: ";
	cout << Shape::getNumShapes() << endl; // Outputs the current number of shapes by calling the static function.

	while (!drawObjects.empty()) // Loop continues while the forward list is not empty.
	{
		drawObjects.front()->draw(drawing); // The front most element is drawn by calling the draw function.
		delete drawObjects.front(); // The front most element is then deleted entirely but still remains in the forward list.
		drawObjects.pop_front(); // The front most element is now deleted from the forward list.
	}

	if (drawing.saveBMP(argv[1])) // Drawing is saved as BMP, if successful then a message is displayed.
	{
		cout << argv[1] << " saved successfully" << endl;
	}


	cout << "Number of Shapes: ";
	cout << Shape::getNumShapes(); // Outputs the current number of shapes after they have been drawn by calling the static function.

	char cc;
	cin >> cc; // Asks to input a char so that the output window stays open.
}

COLOUR getColour(char * red, char * green, char * blue) // Defines the getColour function. This function sets the RGB values that was entered by the user and then returns that COLOUR.
{
	COLOUR colour = { (unsigned)(atoi(red)), (unsigned)(atoi(green)), (unsigned)(atoi(blue)) }; // Casts the strings as unsigned integers and adds those RGB values.
	return colour; // returns the COLOUR.
}

COORD getCoordinate(char * row, char * column) // Defines the getCoordinate function. This function sets the row and column that was entered by the user and then returns that COORD.
{
	COORD coordinate;
	coordinate.row = (unsigned)atoi(row); // Casts the string into an unsigned integer and adds the row to the COORD.
	coordinate.col = (unsigned)atoi(column); // Casts the string into an unsigned integer and adds the column to the COORD.

	return coordinate; // Returns the COORD.

}
