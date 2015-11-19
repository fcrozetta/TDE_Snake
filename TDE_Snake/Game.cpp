#pragma once
#include "stdafx.h"

Game * addGame() {
	Game * game = (Game *)malloc(sizeof(Game));
	game->snkHead = SnakeHead();
}