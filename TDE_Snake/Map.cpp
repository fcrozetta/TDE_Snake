#include "stdafx.h"
#include "Map.h"

void drawScreen() {
	/* Draw the screen */
	for (short i = 1; i < HEIGHT; i++) //Draw Left && Right 
	{
		draw({ 0,i }, SIDEWALL);
		draw({ WIDTH,i }, SIDEWALL);
	}

	for (short i = 0; i < WIDTH; i++) //Draw Top && Bottom 
	{
		draw({ i,0 }, TOPWALL);
	    draw({ i,HEIGHT }, TOPWALL);
	}


	// Draw Corners
	draw({ 0,0 }, CORNER);
	draw({ 0,HEIGHT }, CORNER);
	draw({ WIDTH,0 }, CORNER);
	draw({ WIDTH,HEIGHT }, CORNER);
}

void draw(COORD posXY, char symbol) {
   	/* Draw the something */
   	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
   	printf("%c", symbol);
}
