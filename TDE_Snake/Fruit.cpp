#include "stdafx.h"


void spawnFruit(COORD pos) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%c", FRUIT);
}