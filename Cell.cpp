#include "Cell.h"

Cell::Cell(int i, int j)
{
	this->i = i;
	this->j = j;
}

void Cell::drawLine(Vector2f a, Vector2f b, RenderWindow* window)
{
	Vertex line[] =
	{
		Vertex(a),
		Vertex(b)
	};
	window->draw(line, 2, Lines);
}

void Cell::draw(RenderWindow* window)
{
	float x = j * cellSize;
	float y = i * cellSize;

	if (walls[0])
	{
		drawLine(Vector2f(x, y), Vector2f(x + cellSize, y), window);
	}
	if (walls[1])
	{
		drawLine(Vector2f(x + cellSize, y), Vector2f(x + cellSize, y + cellSize), window);
	}
	if (walls[2])
	{
		drawLine(Vector2f(x + cellSize, y + cellSize), Vector2f(x, y + cellSize), window);
	}
	if (walls[3])
	{
		drawLine(Vector2f(x, y + cellSize), Vector2f(x, y), window);
	}
	if (visited)
	{
		RectangleShape rectangle(Vector2f(cellSize, cellSize));
		rectangle.setPosition(Vector2f(x, y));
		rectangle.setFillColor(Color(255, 0, 255, 200));
		window->draw(rectangle);
	}
}

int Cell::index(int i, int j, const int rows, const int cols)
{
	if (i < 0 || j < 0 || i > rows - 1 || j > cols - 1)
		throw 'e';
	return i * cols + j;
}

Cell* Cell::getNeighbours(vector<Cell>* vc, const int rows, const int cols)
{
	std::vector<Cell*> neighbours;

	try
	{
		Cell* top = &vc->at(index(i - 1, j, rows, cols));
		if (!top->visited)
			neighbours.push_back(top);
	}
	catch (char e){}
	try
	{
		Cell* right = &vc->at(index(i, j + 1, rows, cols));
		if (!right->visited)
			neighbours.push_back(right);
	}
	catch (char e){}
	try
	{
		Cell* bottom = &vc->at(index(i + 1, j, rows, cols));
		if (!bottom->visited)
			neighbours.push_back(bottom);
	}
	catch (char e){}
	try
	{
		Cell* left = &vc->at(index(i, j - 1, rows, cols));
		if (!left->visited)
			neighbours.push_back(left);
	}
	catch (char e){}
	
	if (neighbours.size() > 0)
	{
		
		int r = (rand() % neighbours.size());
		return neighbours.at(r);
	}
	else
		return nullptr;
}

void Cell::highlight(RenderWindow* window)
{
	float x = j * cellSize;
	float y = i * cellSize;

	RectangleShape rectangle(Vector2f(cellSize, cellSize));
	rectangle.setPosition(Vector2f(x, y));
	rectangle.setFillColor(Color(0, 255, 255, 200));
	window->draw(rectangle);
}

Cell::~Cell(){}