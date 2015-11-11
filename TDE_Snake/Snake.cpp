#pragma once
#include "stdafx.h"
#include "Snake.h"


SnakeHead newSnake() {
	return SnakeHead();
}

void addScore(SnakeHead * snake, int score=1) {
	snake->score += score;
}

void addSnakeBody(SnakeHead * snake)
{
	// Implementar adição de corpo no fim do snake
}

void drawSnake(SnakeHead * snake) {
	// Adjust and print Snake Symbol
	switch (snake->direction)
	{
	case Direction::NORTH:
		snake->symbol = '^';
		break;
	case Direction::SOUTH:
		snake->symbol = 'v';
		break;
	case Direction::EAST:
		snake->symbol = '>';
		break;
	case Direction::WEST:
		snake->symbol = '<';
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), snake->pos);
	printf("%c", snake->symbol);
}