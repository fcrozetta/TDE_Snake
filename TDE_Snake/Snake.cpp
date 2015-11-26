#pragma once
#include "stdafx.h"
#include "Snake.h"


SnakeHead *newSnake() {
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
	head->name;
	head->fruitPos = { 0,0 };
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

void printScore(SnakeHead *snake) {
	COORD scorePosition = { 0,HEIGHT + 1 };
	cursorPosition(scorePosition);
	printf("%d", snake->score);
}

void addScore(SnakeHead * snake, int score=1) {
	snake->score += score;
	printScore(snake);
	
	
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
	cursorPosition(snake->pos);
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

	cursorPosition(snake->pos);
	printf("%c", snake->symbol);

	if (snake->next != NULL)
	{
		SnakeBody *tmp = snake->next;
		while (tmp != NULL)
		{
			cursorPosition(tmp->pos);
			char symbol;

			if (tmp->prev == NULL)
			{
				/* Adjust the Symbol to print, if there is no previous body (first body) */
				switch (tmp->direction)
				{
				case NORTH:
					switch (snake->direction)
					{
					case NORTH:
						printf("%c", BODY_VERTICAL);
						break;
					case SOUTH:
						printf("%c", BODY_VERTICAL);
						break;
					case EAST:						
						printf("%c", BODY_NORTH_EAST);
						break;
					case WEST:
						printf("%c", BODY_NORTH_WEST);
						break;
					}
					break;
				case SOUTH:
					switch (snake->direction)
					{
					case NORTH:
						printf("%c", BODY_VERTICAL);
						break;
					case EAST:
						printf("%c", BODY_SOUTH_EAST);
						break;
					case SOUTH:
						printf("%c", BODY_VERTICAL);
						break;
					case WEST:
						printf("%c", BODY_SOUTH_WEST);
						break;
					}
					break;
				case EAST:
					switch (snake->direction)
					{
					case NORTH:
						printf("%c", BODY_SOUTH_WEST);
						break;
					case EAST:
						printf("%c", BODY_HORIZONTAL);
						break;
					case SOUTH:
						printf("%c", BODY_NORTH_WEST);
						break;
					case WEST:
						printf("%c", BODY_HORIZONTAL);
						break;
					default:
						break;
					}
					break;
				case WEST:
					switch (snake->direction)
					{
					case NORTH:
						printf("%c", BODY_SOUTH_EAST);
						break;
					case EAST:
						printf("%c", BODY_HORIZONTAL);
						break;
					case SOUTH:
						printf("%c", BODY_NORTH_EAST);
						break;
					case WEST:
						printf("%c", BODY_HORIZONTAL);
						break;
					}
					break;
				}
				
			}
			else
			{
				/* Adjust the symbol to print, and if its a turn, then print on the previous body position */
				switch (tmp->direction)
				{
				case NORTH:
					switch (tmp->prev->direction)
					{
					case NORTH:
						printf("%c", BODY_VERTICAL);
						break;
					case SOUTH:
						printf("%c", BODY_VERTICAL);
						break;
					case EAST:
						cursorPosition(tmp->prev->pos);
						printf("%c", BODY_NORTH_EAST);
						break;
					case WEST:
						cursorPosition(tmp->prev->pos);
						printf("%c", BODY_NORTH_WEST);
						break;
					}
					break;
				case SOUTH:
					switch (tmp->prev->direction)
					{
					case NORTH:
						printf("%c", BODY_VERTICAL);
						break;
					case EAST:
						cursorPosition(tmp->prev->pos);
						printf("%c", BODY_SOUTH_EAST);
						break;
					case SOUTH:
						printf("%c", BODY_VERTICAL);
						break;
					case WEST:
						cursorPosition(tmp->prev->pos);
						printf("%c", BODY_SOUTH_WEST);
						break;
					}
					break;
				case EAST:
					switch (tmp->prev->direction)
					{
					case NORTH:
						cursorPosition(tmp->prev->pos);
						printf("%c", BODY_SOUTH_WEST);
						break;
					case EAST:
						printf("%c", BODY_HORIZONTAL);
						break;
					case SOUTH:
						cursorPosition(tmp->prev->pos);
						printf("%c", BODY_NORTH_WEST);
						break;
					case WEST:
						printf("%c", BODY_HORIZONTAL);
						break;
					default:
						break;
					}
					break;
				case WEST:
					switch (tmp->prev->direction)
					{
					case NORTH:
						cursorPosition(tmp->prev->pos);
						printf("%c", BODY_SOUTH_EAST);
						break;
					case EAST:
						printf("%c", BODY_HORIZONTAL);
						break;
					case SOUTH:
						cursorPosition(tmp->prev->pos);
						printf("%c", BODY_NORTH_EAST);
						break;
					case WEST:
						printf("%c", BODY_HORIZONTAL);
						break;
					}
					break;
				}
			}

			if (tmp->next == NULL)
			{
				cursorPosition(tmp->lastPos);
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

	if ((snake->nextPosSymbol != ' ') && (snake->nextPosSymbol != FRUIT))
	{
		// Implement Death Functions
		DeathScreen(snake);
		while (!_kbhit())
		{
			continue;
		}
		exit(0);
	}
	if (snake->nextPosSymbol == FRUIT)
	{
		addScore(snake);
		snake->digesting = true;
	}
	drawSnake(snake);
}