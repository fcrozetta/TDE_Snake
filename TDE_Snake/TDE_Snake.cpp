// TDE_Snake.cpp : Defines the entry point for the console application.
//


/* Guias para fazer isso tudo Funcionar:
	- cabeça do Snake Andar na tela		[OK]
	- Frutas aparecerem na tela			[OK]	
	- Snake comer frutas				[OK]
	- Corpo do snake seguindo cabeça	[OK]
	- Incrementar Corpo					[OK]
	- Snake morre ao acertar a parede (snake.. snAKE?, SNAAAAAKE!!!!) [OK]
	- Organizar Menus, para aceitar ESC durante o game [OK]
	- Carregar Jogo						
	- Salvar jogo						

*/
#include "stdafx.h"

int main()
{
	/* Those two should be on start of main, or it will cause failure. Cathastrophic failure... i don't know why */
	char buf[BUFSIZ];
	DWORD num_read;

	srand(time(NULL)); // Seed for random numbers

	setlocale(LC_ALL, "UTF-8");
	SnakeHead * snake = newSnake();
	MainMenu(snake);

	/* Start with a body and tail */
	if (snake->next == NULL)
	{
		SnakeBody * body = newBody();
		SnakeBody * tail = newBody();
		addSnakeBody(snake, body);
		addSnakeBody(snake, tail);
	}
	/*Iniciar o jogo*/
	system("cls");
	drawScreen();
	drawSnake(snake);
		
	/* I'm repeating this block of code, because i'm stupid enough to not create a propper function. sorry */
	buf[0] = '+';
	COORD fruitPos;
	if ((snake->fruitPos.X == 0) && (snake->fruitPos.Y == 0))
	{
		while (buf[0] != ' ')
		{
			fruitPos = { rand() % WIDTH,rand() % HEIGHT };
			ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR)buf, (DWORD)BUFSIZ, fruitPos, (LPDWORD)&num_read);
		}
		snake->fruitPos = fruitPos;
		
	}
	spawnFruit(fruitPos);
	
	
		
	while (true) 
	{
		if (_kbhit())
		{
			/* This is used to get keyboard arrows*/
			int KeyStroke;
			KeyStroke = _getch();
			if (!KeyStroke || KeyStroke == 0xe0)
				KeyStroke = _getch();

			switch (KeyStroke)
			{
			case 27: //ESC: Should open the Menu
				/* Implement Pause Menu */
				PauseMenu(snake);
				drawScreen();
				drawSnake(snake);
				printScore(snake);
				spawnFruit(snake->fruitPos);
				break;
			case 72: //North
				snake->direction = NORTH;
				break;
			case 80: //South
				snake->direction = SOUTH;
				break;
			case 77: //East
				snake->direction = EAST;
				break;
			case 75: //West
				snake->direction = WEST;
				break;
			}
		}

		/* This switch is needed to update the nextPosSymbol. I don't know how to read the console outside the main */
		COORD nextPos;
		switch (snake->direction)
		{
		case NORTH:
			nextPos = { snake->pos.X,snake->pos.Y - 1 };
			break;
		case SOUTH:
			nextPos = { snake->pos.X,snake->pos.Y + 1 };
			break;
		case EAST:
			nextPos = { snake->pos.X + 1,snake->pos.Y };
			break;
		case WEST:
			nextPos = { snake->pos.X - 1,snake->pos.Y };
			break;
		}
		ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR)buf, (DWORD)BUFSIZ, nextPos, (LPDWORD)&num_read);
		snake->nextPosSymbol = buf[0];
		updateSnake(snake);

		// Spawns a new Fruit if snake just ate
		if (snake->digesting)
		{
			snake->digesting = false;
			SnakeBody * body = newBody();
			addSnakeBody(snake, body);
			buf[0] = '+';
			COORD fruitPos;
			while (buf[0] != ' ')
			{
				fruitPos = { rand() % WIDTH,rand() % HEIGHT };
				ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR)buf, (DWORD)BUFSIZ, fruitPos, (LPDWORD)&num_read);
			}
			snake->fruitPos = fruitPos;
			spawnFruit(fruitPos);
		}
		Sleep(100);
	}
	return 0;
}