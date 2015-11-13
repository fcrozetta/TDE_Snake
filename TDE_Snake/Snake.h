#pragma once
enum Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct snakebody {
	COORD pos;
	char symbol = '*';
	struct snakebody * next = NULL;
	struct snakebody * prev = NULL;
}SnakeBody;

typedef struct snakehead
{
	COORD pos = { WIDTH/2,HEIGHT/2 };
	Direction direction = SOUTH;
	int score = 0;
	char symbol;
	char nextPosSymbol;
	SnakeBody * next = NULL;
}SnakeHead;

void addScore(SnakeHead * snake, int score);

void addSnakeBody(SnakeHead *snake);

void drawSnake(SnakeHead * snake);

void updateSnake(SnakeHead * snake);
