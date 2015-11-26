#include "stdafx.h"
#include "Menu.h"

void printMenu(char * menuFile) {
	int ch;
	FILE * menu;
	fopen_s(&menu, menuFile, "r");
	if (menu == NULL) exit;
	while ((ch = fgetc(menu)) != EOF)
	{
		printf("%c", ch);
	}

	fclose(menu);
}

void MainMenu(SnakeHead * snake) {
	char name[10] = " ";
	system("cls");
	char * menu= "MainMenu.txt";
	printMenu(menu);
	char ch;
	while (!_kbhit())
	{
		ch = _getch();

		if (ch == '1') // New Game
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 3,HEIGHT -1 });
			printf("Digite o seu Nome: ");
			scanf_s("%9s", name,sizeof(name));
			strcpy_s(snake->name,sizeof(name), name);
			break;
		}
		else if(ch == '2') // Load Game
		{
			/* Implement Load Game */
			break;
		}
		else if(ch == '0') // Exit
		{
			exit(0);
			break;
		}
		else
		{
			continue;
		}

	}

}

void PauseMenu(SnakeHead * snake) {
	char * menu = "PauseMenu.txt";
	COORD pos = { 0,0 };
	cursorPosition(pos);
	printMenu(menu);
	char ch;
	while (!_kbhit())
	{
		ch = _getch();

		if (ch == '1') // Save
		{
			SaveGame(snake);
			break;
		}
		else if (ch == '2') // Load Game
		{
			/* Implement Load Game */
			break;
		}
		else if (ch == '0') // Exit
		{
			break;
		}
		else
		{
			continue;
		}

	}
}

void SaveGame(SnakeHead * snake) {
	//TODO: Add correct Data to save
	FILE * save;
	char fileName[14] = "";
	strcat_s(fileName,snake->name);
	strcat_s(fileName, ".txt");
	
	COORD pos = { 0,0 };
	cursorPosition(pos);
	printf("%s", fileName);
	Sleep(1000);
	fopen_s(&save, fileName , "w");
	fprintf(save, "%d;%d;%d;%d;%d,%d;%d;%d;%d;%c;%c;%d;%s\n",
		snake->pos.X, snake->pos.Y, snake->lastPos.X, snake->lastPos.Y, snake->fruitPos.X, snake->fruitPos.Y, 
		snake->direction, snake->lastDirection, snake->score, snake->symbol, snake->nextPosSymbol,snake->digesting,
		snake->name);
	fclose(save);
}

void LoadGame(SnakeHead * snake) {
	//Implement Load Game
	FILE * load;
	//char teste;
	fopen_s(&load, "Save.txt", "r");
	if (load == NULL) exit(-1);
	//fscanf_s(load, "%c", &teste);
	fclose(load);
}

void DeathScreen(SnakeHead * snake) {
	/// Start to print on col 6, row 6
	system("cls");
	char * menu = "DeathScreen.txt";
	printMenu(menu);
	for (int i = 0; i < 10; i++)
	{

		COORD scorePos = { 6, 6+i };
		cursorPosition(scorePos);
		printf("%d.", i+1);
	}
	COORD scorePos = { 9,6 };
	cursorPosition(scorePos);
	printf("%s - %d",snake->name, snake->score);
	

}