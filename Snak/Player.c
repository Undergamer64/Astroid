#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Player.h"

void Move(struct vaisseau player) {
	float dirx = cos(player.angle * 3.1415 / 180);
	float diry = sin(player.angle * 3.1415 / 180);
	if (sfKeyboard_isKeyPressed(sfKeyRight)) {
		player.angle += 5;

	}
	if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
		player.angle -= 5;

	}
	if (sfKeyboard_isKeyPressed(sfKeyUp)) {
		player.x += 5 * dirx;
		player.y += 5 * diry;
	}
}