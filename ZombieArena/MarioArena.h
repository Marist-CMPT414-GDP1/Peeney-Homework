#pragma once
#include "Enemy.h"

using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena);
Enemy* createHorde(int numEnemies, IntRect arena);
