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
	Sleep(75); //controlling board update speed
	system("cls"); //clears console screen
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
				cout << "O"; //prints head 
			else if (i == fruitY && j == fruitX)
				cout << "X"; //prints fruit
			else
			{
				bool print = false; //keeps track of wether we printed the tail segment or not
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i) // j == current x coordinate; i == current y coordinate
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
	for (int i = nTail; i > 0; i--)
	{

		tailX[i] = tailX[i - 1];

		tailY[i] = tailY[i - 1];

	}
	tailX[0] = x;
	tailY[0] = y;

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

	for (int i = 0; i < nTail; i++) //check if we hit ourselves
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		nTail++;
		score += 10; //increase score 
		//new fruit pos
		fruitX = rand() % width;
		fruitY = rand() % height;
	}

}

int main()
{
	Setup(); //prepares some game logic before the games stars
	while (!gameOver) //main game loop
	{
		Draw(); //draws game board
		Input(); //gets player input
		Logic(); //Deals with updating tail body, checking if we lost
	}
	cout << endl << "Thanks for playing!";
	return 0;
}
