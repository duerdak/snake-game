#include <iostream>
#include <conio.h> //for input function
#include <windows.h> //for sleep
#include <vector>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score; //x,y are the snake's heads' position
int tailX[100], tailY[100]; //store body's location, last position in the arrays' is the last piece of the body before the head
int nTail = 0; //length of tail, 0 at start
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	// snake starts in the middle
	x = width / 2;
	y = height / 2;
	//random pos for the fruit
	fruitX = rand() % width; //not trully randomized fruit position
	fruitY = rand() % height; //not trully randomized fruit position
	score = 0;
}

void Draw()
{
	system("cls");
	// top border of map
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	// walls of the map
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#"; //draw left side of wall
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "X";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "#"; //draw right side of wall
		}
		cout << endl;
	}
	// bottom border of map
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl << "Score: " << score << endl;
}

void Input()
{
	if (_kbhit()) //checks if keyboard button is pressed
	{
		switch (_getch()) //returns ASCII value of pressed button
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0], prevY = tailY[0], prev2X, prev2Y;
	tailX[0] = x; //body positionX before head
	tailY[0] = y; //body positionY before head
	for (int i = 1; i < nTail; i++) //starts at 1 because pos 0 is recorded at the upper two rows
	{
		prev2X = tailX[i]; //stores Oo[o] position
		prev2Y = tailY[i]; //stores Oo[o] position
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	/*if (x > width || x < 0 || y > height ||  y < 0) //walls kill you
		gameOver = true;*/

	if (x >= width) x = 0; else if (x < 0) x = width - 1; //if you want to pass through the walls of the map
	if (y >= height) y = 0; else if (y < 0) y = height - 1; //if you want to pass through the bottom and top of the map

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		nTail++;
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}

}

int main()
{
	Setup();
	while (!gameOver) //main game loop
	{
		Draw();
		Input();
		Logic();
		Sleep(50); //controlling board update speed
	}
	cout << endl << "Thanks for playing!";
	return 0;
}
