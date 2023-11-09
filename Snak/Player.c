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
		player.force.x += 0.5 * dirx * delta / 10000;
		player.force.y += 0.5 * diry * delta / 10000;
	}

	player.x += player.force.x;
	player.y += player.force.y;

	float a_length = sqrt(player.force.x * player.force.x + player.force.y * player.force.y);
	if (a_length != 0) {
		float normalized_x = player.force.x / a_length;
		float normalized_y = player.force.y / a_length;

		player.force.x -= (0.2 * delta / 10000) * normalized_x ;
		player.force.y -= (0.2 * delta / 10000) * normalized_y ;
	}
}