#include "Cell.h"
#include <thread>

using namespace this_thread;

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

const int rows = WINDOW_HEIGHT / cellSize;
const int cols = WINDOW_WIDTH / cellSize;

vector<Cell> vc;
vector<Cell*> stack;

void removeWalls(Cell* a, Cell* b)
{
	int x = a->j - b->j;
	
	if (x == 1)
	{
		a->walls[3] = false;
		b->walls[1] = false;
	}
	else if (x == -1)
	{
		a->walls[1] = false;
		b->walls[3] = false;
	}

	int y = a->i - b->i;
	if (y == 1)
	{
		a->walls[0] = false;
		b->walls[2] = false;
	}
	else if (y == -1)
	{
		a->walls[2] = false;
		b->walls[0] = false;
	}
}

int main()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			vc.push_back(Cell{i, j});
		}

	Cell* current = &vc.at(0);
	current->visited = true;
	

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Maze ");
	Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		window.clear(Color(127, 118, 121));
		
		for (Cell c : vc)
		{
			c.draw(&window);
		}

		current->highlight(&window);

		Cell* next = current->getNeighbours(&vc, rows, cols);
		if (next)
		{
			next->visited = true;

			stack.push_back(current);

			removeWalls(current, next);
			current = next;
		}
		else if (!stack.empty())
		{
			current = stack.back();
			stack.pop_back();
		}

		window.display();
		//sleep_for(50ms);
	}
}