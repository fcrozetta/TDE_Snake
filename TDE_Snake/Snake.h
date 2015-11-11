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
	COORD pos;
	Direction direction;
	int score;
	char symbol = '<';
	SnakeBody * next = NULL;
}SnakeHead;

void addScore(SnakeHead * snake, int score);

void addSnakeBody(SnakeHead *snake);