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

char MainMenu() {
	system("cls");
	char * map = "MainMenu.txt";
	printMenu(map);
	while (!_kbhit())
	{
		continue;
	}
	return (char)_getch();
}

void SaveGame(Game * game) {
	//TODO: Add correct Data to save
	FILE * save;
	fopen_s(&save, "Save.txt", "w");
	fprintf(save, "%d", 0);
	fclose(save);
}

void LoadGame() {
	//Implement Load Game
	FILE * load;
	//char teste;
	fopen_s(&load, "Save.txt", "r");
	if (load == NULL) exit(-1);
	//fscanf_s(load, "%c", &teste);
	fclose(load);
}