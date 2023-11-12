#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Player.h"
#include "Bullet.h"

#define PI 3.1415926535

int speed_bullet = 1;

void Create_bullet(struct vaisseau player, struct bullet list_bullet[], int size[], int nb_bullet) {
	//creation de nouvelle balle
	list_bullet[nb_bullet].x = player.x;
	list_bullet[nb_bullet].y = player.y;
	list_bullet[nb_bullet].angle = player.angle;
	list_bullet[nb_bullet].vitesse = speed_bullet;
	list_bullet[nb_bullet].shape = sfRectangleShape_create();
	sfRectangleShape_setSize(list_bullet[nb_bullet].shape, (sfVector2f){ size[0] * 25 / 1920, size[0] * 25 / 1920});
	sfRectangleShape_setOrigin(list_bullet[nb_bullet].shape, (sfVector2f){ size[0] * 12.5 / 1920, size[0] * 12.5 / 1920});
	sfRectangleShape_setRotation(list_bullet[nb_bullet].shape, list_bullet[nb_bullet].angle);
	sfRectangleShape_setPosition(list_bullet[nb_bullet].shape, (sfVector2f) { list_bullet[nb_bullet].x, list_bullet[nb_bullet].y });
	nb_bullet += 1;
}

void Move_bullets(struct bullet list_bullet[], int nb_bullet, int delta) {
	for (int i = 0; i < nb_bullet; i++) {
		float dirx = cos(list_bullet[i].angle * PI / 180);
		float diry = sin(list_bullet[i].angle * PI / 180);

		list_bullet[i].x += list_bullet[i].vitesse * dirx * delta / 10000;
		list_bullet[i].y += list_bullet[i].vitesse * diry * delta / 10000;
		sfRectangleShape_setPosition(list_bullet[nb_bullet].shape, (sfVector2f) { list_bullet[nb_bullet].x, list_bullet[nb_bullet].y });
	}
}