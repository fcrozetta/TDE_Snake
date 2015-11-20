#pragma once
enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

typedef struct snakebody {
	COORD pos;
	COORD lastPos;
	Direction direction;
	Direction lastDirection;
	struct snakebody * next = NULL;
	struct snakebody * prev = NULL;
}SnakeBody;

typedef struct snakehead
{
	COORD pos = { WIDTH/2,HEIGHT/2 };
	COORD lastPos;
	Direction direction = SOUTH;
	Direction lastDirection = SOUTH;
	int score = 0;
	char symbol;
	char nextPosSymbol;
	bool digesting = false;
	SnakeBody * next = NULL;
}SnakeHead;

SnakeHead * newSnake();

SnakeBody * newBody();

void addScore(SnakeHead * snake, int score);

void addSnakeBody(SnakeHead * snake, SnakeBody * body);

void drawSnake(SnakeHead * snake);

void updateSnake(SnakeHead * snake);
