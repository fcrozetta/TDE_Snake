// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#define HEIGHT 23
#define WIDTH 79
#define SIDEWALL '|'
#define TOPWALL '-'
#define CORNER '+'
#define FRUIT '*'
#define BODY_HORIZONTAL 205
#define BODY_VERTICAL 186
#define BODY_NORTH_WEST 187
#define BODY_NORTH_EAST 201
#define BODY_SOUTH_WEST 188
#define BODY_SOUTH_EAST 200
#define cursorPosition(x) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), x);

#include <locale.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#include "Map.h"
#include "Snake.h"
#include "Fruit.h"

#include "Menu.h"