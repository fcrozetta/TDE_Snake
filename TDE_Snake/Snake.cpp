#pragma once
#include "stdafx.h"
#include "Snake.h"


SnakeHead *newSnake() {
	/* Continue From here */
	SnakeHead * head = (SnakeHead *)malloc(sizeof(SnakeHead));
	head->digesting = false;
	head->direction = SOUTH;
	head->lastDirection = head->direction;
	head->pos = { WIDTH / 2,HEIGHT / 2 };
	head->lastPos = head->pos;
	head->nextPosSymbol;
	head->next = NULL;
	head->score = 0;
	head->symbol;
	return head;
}

SnakeBody * newBody() {
	SnakeBody * body = (SnakeBody *)malloc(sizeof(snakebody));

	body->next = NULL;
	body->lastPos = { 0,0 };
	body->pos = { 0,0 };
	body->prev = NULL;
	body->direction=NORTH;
	body->lastDirection = NORTH;
	return body;
}

void addScore(SnakeHead * snake, int score=1) {
	snake->score += score;
}

void addSnakeBody(SnakeHead * snake, SnakeBody * body)
{
	SnakeBody * last = snake->next;
	// Implementar adição de corpo no fim do snake
	if (last != NULL)
	{
		while (last->next != NULL)
		{
			last = last->next;
		}
		body->prev = last;
		last->next = body;
		body->pos = last->lastPos;
		body->direction = last->lastDirection;
	}
	else
	{
		body->prev = NULL;
		body->next = NULL;
		body->pos = snake->lastPos;
		body->direction = snake->lastDirection;
		snake->next = body;
	}
}

void drawSpaceSnake(SnakeHead * snake) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), snake->pos);
	printf("%c", ' ');
}

void drawSnake(SnakeHead * snake) {
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

	if (snake->next != NULL)
	{
		SnakeBody *tmp = snake->next;
		while (tmp != NULL)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp->pos);
			char symbol;
			tmp->direction % 2 == 0 ? symbol = BODY_VERTICAL : symbol = BODY_HORIZONTAL;
			printf("%c", symbol);
			if (tmp->next == NULL)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp->lastPos);
				printf("%c", ' ');
			}
			
			tmp = tmp->next;
		}
	}
	
}

void updateSnake(SnakeHead * snake) {
	drawSpaceSnake(snake);
	snake->lastPos = snake->pos;
	snake->lastDirection = snake->direction;
	/* This function will get the next position, check if is a hit, score or move, and call the right function */
	switch (snake->direction)
	{
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
	/* Update the snake body */
	SnakeBody * tmp = snake->next;
	if (tmp != NULL)
	{
		tmp->lastPos = tmp->pos;
		tmp->lastDirection = tmp->direction;
		tmp = tmp->next;
		while (tmp != NULL)
		{
			/* LastPosition of every block */
			tmp->lastPos = tmp->pos;
			tmp->lastDirection = tmp->direction;
			tmp = tmp->next;
		}

		/* Updates the body positions */
 		tmp = snake->next;
		tmp->pos = snake->lastPos;
		tmp->direction = snake->lastDirection;
		if (tmp->next != NULL)
		{
			tmp = tmp->next;
			while (tmp != NULL)
			{
				tmp->pos = tmp->prev->lastPos;
				tmp->direction = tmp->prev->lastDirection;
				tmp = tmp->next;
			}
		}
		
	}

	if ((snake->nextPosSymbol == SIDEWALL) || (snake->nextPosSymbol == TOPWALL))
	{
		// Implement Deah Functions
		printf("Morreu, babaca!");
	}
	if (snake->nextPosSymbol == FRUIT)
	{
		addScore(snake);
		snake->digesting = true;
	}
	drawSnake(snake);
}