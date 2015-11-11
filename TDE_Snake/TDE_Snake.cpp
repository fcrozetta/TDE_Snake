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
	setlocale(LC_ALL, "");
	Game game = Game();
	switch ((int)MainMenu())
	{
	case 48:
		exit(0);
		break;
	case 49:
		/*Iniciar o jogo*/
		system("cls");
		drawScreen();
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

