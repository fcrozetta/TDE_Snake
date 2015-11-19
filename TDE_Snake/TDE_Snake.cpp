// TDE_Snake.cpp : Defines the entry point for the console application.
//


/* Guias para fazer isso tudo Funcionar:
	- cabeça do Snake Andar na tela		[OK]
	- Frutas aparecerem na tela			[OK]	
	- Snake comer frutas				[OK]
	- Corpo do snake seguindo cabeça
	- Incrementar Corpo
	- Snake morre ao acertar a parede (snake.. snAKE?, SNAAAAAKE!!!!)

*/
#include "stdafx.h"


int main()
{
	/* Those two should be on start of main, or it will cause failure. Cathastrophic failure... i don't know why */
	char buf[BUFSIZ];
	DWORD num_read;

	srand(time(NULL)); // Seed for random numbers

	setlocale(LC_ALL, "");
	SnakeHead * snake;
	switch ((int)MainMenu())
	{
	case 27: // Esc <- Save this to use later
		printf("HELLO MOTHERFUCKER");
		break;
	case 48:
		exit(0);
		break;
	case 49:
		/*Iniciar o jogo*/
		system("cls");
		drawScreen();
		drawSnake(game->snkHead);
		
		/* I'm repeating this block of code, because i'm stupid enough to not create a propper function. sorry */
		buf[0] = '+';
		COORD fruitPos;
		while (buf[0] != ' ')
		{
			fruitPos = { rand() % WIDTH,rand() % HEIGHT };
			ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR)buf, (DWORD)BUFSIZ, fruitPos, (LPDWORD)&num_read);
		}
		spawnFruit(fruitPos);
		
		while (true) 
		{
			// Spawns a new Fruit if snake just ate
			if (game->snkHead->digesting)
			{
				game->snkHead->digesting = false;
				SnakeBody * body = newBody();
				addSnakeBody(game->snkHead, body);
				buf[0] = '+';
				COORD fruitPos;
				while (buf[0] != ' ')
				{
					fruitPos = { rand() % WIDTH,rand() % HEIGHT };
					ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR)buf, (DWORD)BUFSIZ, fruitPos, (LPDWORD)&num_read);
				}
				spawnFruit(fruitPos);
			}

			if (_kbhit())
			{
				int KeyStroke;
				KeyStroke = _getch();

				if (!KeyStroke || KeyStroke == 0xe0)
					KeyStroke = _getch();
				switch (KeyStroke)
				{
				case 72: //North
					game->snkHead->direction = NORTH;
					break;
				case 80: //South
					game->snkHead->direction = SOUTH;
					break;
				case 77: //East
					game->snkHead->direction = EAST;
					break;
				case 75: //West
					game->snkHead->direction = WEST;
					break;
				}
			}

			/* This switch is needed to update the nextPosSymbol. I don't know how to read the console outside the main */
			COORD nextPos;
			switch (game->snkHead->direction)
			{
			case NORTH:
				nextPos = { game->snkHead->pos.X,game->snkHead->pos.Y - 1 };
				break;
			case SOUTH:
				nextPos = { game->snkHead->pos.X,game->snkHead->pos.Y + 1 };
				break;
			case EAST:
				nextPos = { game->snkHead->pos.X + 1,game->snkHead->pos.Y };
				break;
			case WEST:
				nextPos = { game->snkHead->pos.X - 1,game->snkHead->pos.Y };
				break;
			}
			ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR)buf, (DWORD)BUFSIZ, nextPos, (LPDWORD)&num_read);
			game->snkHead->nextPosSymbol = buf[0];
			updateSnake(game->snkHead);
			Sleep(100);
		}
		break;
	case 50:
		SaveGame(game);
		break;

	case 51:
		LoadGame();
		break;
	default:
		break;
	}

	return 0;
}

