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
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 3,HEIGHT - 1 });
			printf("Digite o seu Nome: ");
			scanf_s("%9s", name, sizeof(name));
			strcpy_s(snake->name, sizeof(name), name);
			LoadGame(snake);
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
			LoadGame(snake);
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
	// Save the snakeHead
	fprintf(save, "%d %d %d %d %d %d %d %d %d %c %c %d %s",
		snake->pos.X, snake->pos.Y, snake->lastPos.X, snake->lastPos.Y, snake->fruitPos.X, snake->fruitPos.Y, 
		snake->direction, snake->lastDirection, snake->score, snake->symbol, snake->nextPosSymbol ,snake->digesting,
		snake->name);
	
	// Save SnakeBody
	SnakeBody * tmp = snake->next;
	
	while (tmp != NULL)
	{
		fprintf(save, "\n%d %d %d %d %d %d", 
			tmp->pos.X, tmp->pos.Y, tmp->lastPos.X, tmp->lastPos.Y, tmp->direction, tmp->lastDirection);
		tmp = tmp->next;
	}
	fclose(save);
}

void LoadGame(SnakeHead * snake) {
	//Implement Load Game
	FILE * load;
	char fileName[14] = "";
	strcat_s(fileName, snake->name);
	strcat_s(fileName, ".txt");
	fopen_s(&load, fileName, "r");
	fscanf_s(load, "%d", &snake->pos.X);
	fscanf_s(load, "%d", &snake->pos.Y);
	fscanf_s(load, "%d", &snake->lastPos.X);
	fscanf_s(load, "%d", &snake->lastPos.Y);
	fscanf_s(load, "%d", &snake->fruitPos.X);
	fscanf_s(load, "%d", &snake->fruitPos.Y);
	fscanf_s(load, "%d", &snake->direction);
	fscanf_s(load, "%d", &snake->lastDirection);
	fscanf_s(load, "%d", &snake->score);
	fscanf_s(load, " %c", &snake->symbol,sizeof(snake->symbol));
	fscanf_s(load, "%c", &snake->nextPosSymbol, sizeof(snake->nextPosSymbol));
	fscanf_s(load, "%d", &snake->digesting);
	fscanf_s(load, "%s", &snake->name,sizeof(snake->name));

	
	SnakeBody * body = newBody();
	fscanf_s(load, "%d",&body->pos.X);
	fscanf_s(load, "%d", &body->pos.Y);
	fscanf_s(load, "%d", &body->lastPos.X);
	fscanf_s(load, "%d", &body->lastPos.Y);
	fscanf_s(load, "%d", &body->direction);
	fscanf_s(load, "%d", &body->lastDirection);
	body->prev = NULL;
	body->next = NULL;
	snake->next = body;

	while (!feof(load))
	{
		SnakeBody * tail = newBody();
		fscanf_s(load, "%d", &body->pos.X);
		fscanf_s(load, "%d", &body->pos.Y);
		fscanf_s(load, "%d", &body->lastPos.X);
		fscanf_s(load, "%d", &body->lastPos.Y);
		fscanf_s(load, "%d", &body->direction);
		fscanf_s(load, "%d", &body->lastDirection);
		body->next = NULL;
		body->prev = NULL;
		SnakeBody * tmp = snake->next;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = tail;
		tail->prev = tmp;
	}

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