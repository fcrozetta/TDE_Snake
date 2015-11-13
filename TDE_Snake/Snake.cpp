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
	case NORTH:
		snake->symbol = '^';
		break;
	case SOUTH:
		snake->symbol = 'v';
		break;
	case EAST:
		snake->symbol = '>';
		break;
	case WEST:
		snake->symbol = '<';
		break;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), snake->pos);
	printf("%c", snake->symbol);
}

void updateSnake(SnakeHead * snake) {
	/* This function will get the next position, check if is a hit, score or move, and call the right function */

	switch (snake->direction)
	{
		// Each case should	
	case NORTH:
		snake->pos.Y -= 1;
		break;
	case SOUTH:
		snake->pos.Y += 1;
		break;
	case EAST:
		snake->pos.X += 1;
		break;
	case WEST:
		snake->pos.X -= 1;
		break;
	}
	if ((snake->nextPosSymbol == SIDEWALL) || (snake->nextPosSymbol == TOPWALL))
	{
		// Implement Deah Functions
		printf("Morreu, babaca!");
	}
	drawSnake(snake);
}