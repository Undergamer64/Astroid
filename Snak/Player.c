#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Player.h"
#include "Bullet.h"

#define PI 3.1415926535

int pressed = 0;

void Move_player(struct vaisseau player, int delta, int size[]) {
	float dirx = cos(player.angle * PI / 180);
	float diry = sin(player.angle * PI / 180);

	if (sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyD)) {
		player.angle += 5 * delta / 10000;

	}
	if (sfKeyboard_isKeyPressed(sfKeyLeft) || sfKeyboard_isKeyPressed(sfKeyQ)) {
		player.angle -= 5 * delta / 10000;

	}
	if (player.angle >= 360 || player.angle <= -360) {
		player.angle = 0;
	}
	if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) {
		if (fabs(player.force.x + player.vitesse * dirx * delta / 10000) < fabs(10 * dirx * delta / 10000)) {
			player.force.x += player.vitesse * dirx * delta / 10000;
		}
		if (fabs(player.force.y + player.vitesse * diry * delta / 10000) < fabs(10 * diry * delta / 10000)) {
			player.force.y += player.vitesse * diry * delta / 10000;
		}

	}
	if (sfKeyboard_isKeyPressed(sfKeyDown) || sfKeyboard_isKeyPressed(sfKeyS)) {
		player.force.x *= 0.9;
		player.force.y *= 0.9;
	}

	player.x += player.force.x;
	player.y += player.force.y;

	float a_length = sqrt(player.force.x * player.force.x + player.force.y * player.force.y);
	if (a_length != 0) {
		float normalized_x = player.force.x / a_length;
		float normalized_y = player.force.y / a_length;
		if (fabs(player.force.x) - fabs((size[0] / 21600.0) * normalized_x) > 0) {
			player.force.x -= ((size[0] / 21600.0) * delta / 10000) * normalized_x;
		}
		else {
			player.force.x = 0;
		}
		if (fabs(player.force.y) - fabs((size[0] / 21600.0) * normalized_y) > 0) {
			player.force.y -= ((size[0] / 21600.0) * delta / 10000) * normalized_y;
		}
		else {
			player.force.y = 0;
		}
	}

	sfText_setPosition(player.text, (sfVector2f) { player.x, player.y });
	sfText_setRotation(player.text, player.angle + 90);
}

void Teleport(struct vaisseau player,int size[]) {
	if (player.x + player.force.x >= size[0] + (sfText_getLocalBounds(player.text).width / 2)) {
		player.x = -sfText_getLocalBounds(player.text).width / 2;
	}
	else if (player.x + player.force.x <= 0 - (sfText_getLocalBounds(player.text).width / 2)) {
		player.x = size[0] + (sfText_getLocalBounds(player.text).width / 2);
	}
	else if (player.y + player.force.y >= size[1] + (sfText_getLocalBounds(player.text).height / 2)) {
		player.y = -sfText_getLocalBounds(player.text).height / 2;
	}
	else if (player.y + player.force.y <= 0 - (sfText_getLocalBounds(player.text).height / 2)) {
		player.y = size[1] + (sfText_getLocalBounds(player.text).height / 2);
	}
}

void Shoot(struct vaiseau *player, struct bullet list_bullet[], int size[], int nb_bullet) {
	if (sfKeyboard_isKeyPressed(sfKeySpace)) {
		if (!pressed) {
			pressed = 1;
			Create_bullet(player, list_bullet, size, nb_bullet);
		}
	}
	else if (pressed) {
		pressed = 0;
	}
}