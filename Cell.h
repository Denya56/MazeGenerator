#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

#define cellSize 12.f

class Cell
{
public:
	int i, j;
	bool walls[4] = {true, true, true, true};
	bool visited = false;
	Cell(int, int);
	void draw(RenderWindow*);
	void drawLine(Vector2f, Vector2f, RenderWindow*);
	Cell* getNeighbours(vector<Cell>*, const int, const int);
	int index(int, int, const int, const int);
	void highlight(RenderWindow*);
	~Cell();
};