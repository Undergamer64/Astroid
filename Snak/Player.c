#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Player.h"
#define PI 3.1415926535

void Move(struct vaisseau player, int delta) {
	float dirx = cos(player.angle * PI / 180);
	float diry = sin(player.angle * PI / 180);
	if (sfKeyboard_isKeyPressed(sfKeyRight)) {
		player.angle += 5 * delta / 10000;

	}
	if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
		player.angle -= 5 * delta / 10000;

	}
	if (player.angle >= 360 || player.angle <= -360) {
		player.angle = 0;
	}
	if (sfKeyboard_isKeyPressed(sfKeyUp)) {
		player.vitesse += 3 * delta / 10000;
	}
	player.x += player.vitesse * dirx;
	player.y += player.vitesse * diry;
	player.vitesse -= 0.5;
	if (player.vitesse < 0) {
		player.vitesse = 0;
	}
}