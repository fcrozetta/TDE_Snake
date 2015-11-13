// TDE_Snake.cpp : Defines the entry point for the console application.
//


/* Guias para fazer isso tudo Funcionar:
	- Tela Padrão, com Bordas
	- cabeça do Snake Andar na tela	
	- Frutas aparecerem na tela
	- Snake comer frutas
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

	setlocale(LC_ALL, "");
	Game game;
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
		drawSnake(&game.snkHead);
		while (true)
		{

			if (_kbhit())
			{
				char pressedKey = _getch();
				printf("%c", pressedKey);
/*				if (pressedKey == 'à') // Up arrow
				{
					game.snkHead.direction = NORTH;
				}
				if (pressedKey == 'B') // Down arrow
				{
					game.snkHead.direction = SOUTH;
				}
				if (pressedKey == 'C') // Right arrow
				{
					game.snkHead.direction = EAST;
				}
				if (pressedKey == 'D') // Left arrow
				{
					game.snkHead.direction = WEST;
				}*/
			}

			/* This switch is needed to update the nextPosSymbol. I don't know how to read the console outside the main */
			COORD nextPos;

			switch (game.snkHead.direction)
			{
			case NORTH:
				nextPos = { game.snkHead.pos.X,game.snkHead.pos.Y - 1 };
				break;
			case SOUTH:
				nextPos = { game.snkHead.pos.X,game.snkHead.pos.Y + 1 };
				break;
			case EAST:
				nextPos = { game.snkHead.pos.X + 1,game.snkHead.pos.Y };
				break;
			case WEST:
				nextPos = { game.snkHead.pos.X - 1,game.snkHead.pos.Y };
				break;
			}
			
			ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR)buf, (DWORD)BUFSIZ, nextPos, (LPDWORD)&num_read);
			game.snkHead.nextPosSymbol = buf[0];
			updateSnake(&game.snkHead);
			Sleep(1000);
		}
		break;
	case 50:
		SaveGame(&game);
		break;

	case 51:
		LoadGame();
		break;
	default:
		break;
	}

	return 0;
}

