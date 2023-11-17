#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"

#define PI 3.1415926535


int First_slot(struct asteroid list_asteroid[], int nb_asteroid) {
	int slot = nb_asteroid;
	for (int i = 0; i < nb_asteroid; i++) {
		if (list_asteroid[i].type == 0) {
			slot = i;
			break;
		}
	}
	return slot;
}

int Are_all_dead(struct asteroid list_asteroid[], int nb_asteroid) {
	for (int i = 0; i < nb_asteroid; i++) {
		if (list_asteroid[i].type) {
			return 0;
		}
	}
	return 1;
}


void Move_asteroid(struct asteroid list_asteroid[],int nb_asteroid, int delta) {
	for (int i = 0; i < nb_asteroid; i++) {
		sfCircleShape_setRadius(list_asteroid[i].shape, list_asteroid[i].type * 20);
		sfCircleShape_setOrigin(list_asteroid[i].shape, (sfVector2f) { list_asteroid[i].type * 20, list_asteroid[i].type * 20 });

		float dirx = cos(list_asteroid[i].angle * PI / 180);
		float diry = sin(list_asteroid[i].angle * PI / 180);

		list_asteroid[i].x += list_asteroid[i].speed * dirx * delta / 10000;
		list_asteroid[i].y += list_asteroid[i].speed * diry * delta / 10000;
	
		sfCircleShape_setPosition(list_asteroid[i].shape, (sfVector2f) { list_asteroid[i].x, list_asteroid[i].y });
	}
}

void Teleport_asteroid(struct asteroid list_asteroid[], int nb_asteroid, int size[], int delta) {
	for (int i = 0; i < nb_asteroid; i++) {
		float dirx = cos(list_asteroid[i].angle * PI / 180);
		float diry = sin(list_asteroid[i].angle * PI / 180);

		if (list_asteroid[i].x + list_asteroid[i].speed * dirx * delta / 10000 >= size[0] + (sfCircleShape_getLocalBounds(list_asteroid[i].shape).width / 2)) {
			list_asteroid[i].x = -sfCircleShape_getLocalBounds(list_asteroid[i].shape).width / 2;
		}
		else if (list_asteroid[i].x + list_asteroid[i].speed * dirx * delta / 10000 <= 0 - (sfCircleShape_getLocalBounds(list_asteroid[i].shape).width / 2)) {
			list_asteroid[i].x = size[0] + (sfCircleShape_getLocalBounds(list_asteroid[i].shape).width / 2);
		}
		else if (list_asteroid[i].y + list_asteroid[i].speed * diry * delta / 10000 >= size[1] + (sfCircleShape_getLocalBounds(list_asteroid[i].shape).height / 2)) {
			list_asteroid[i].y = -sfCircleShape_getLocalBounds(list_asteroid[i].shape).height / 2;
		}
		else if (list_asteroid[i].y + list_asteroid[i].speed * diry * delta / 10000 <= 0 - (sfCircleShape_getLocalBounds(list_asteroid[i].shape).height / 2)) {
			list_asteroid[i].y = size[1] + (sfCircleShape_getLocalBounds(list_asteroid[i].shape).height / 2);
		}
	}
}

void Create_asteroid(struct asteroid list_asteroid[], int nb_asteroid, int size[], int difficulty, int *wave) {
	int speed_asteroid_max = ((int) size[0] / 540)*difficulty/2;
	if (*wave > 6) {
		*wave = 6;
	}
	for (int i = 0; i < nb_asteroid / (10-*wave); i++) {
		list_asteroid[i].type = 3;
		list_asteroid[i].speed = (rand() % speed_asteroid_max);
		int angle = (rand() % 70)+15;
		
		list_asteroid[i].angle = angle * ((rand()%3)+1);

		sfCircleShape_setRadius(list_asteroid[i].shape, list_asteroid[i].type * 20 * size[0] / 1080);
		sfCircleShape_setOrigin(list_asteroid[i].shape, (sfVector2f) { list_asteroid[i].type * 20 * size[0] / 1080, list_asteroid[i].type * 20 * size[0] / 1080});

		int temp = rand() % 2;
		printf("%d", temp);
		if (temp == 1) {
			int X = rand() % size[0];
			list_asteroid[i].x = X;
			list_asteroid[i].y = -3 * 20 * size[0] / 1080;
 		}
		else {
			int Y = rand() % size[1];
			list_asteroid[i].x = -3 * 20 * size[0] / 1080;
			list_asteroid[i].y = Y;
		}
	}
	*wave += 1;
}

void Division(struct asteroid list_asteroid[], int asteroid, float *angle, int nb_asteroid) {
	list_asteroid[asteroid].type -= 1;
	printf("%f\n", *angle);
	list_asteroid[asteroid].angle = *angle + (float)(rand() % 90) - 22.5;
	int i_asteroid = First_slot(list_asteroid, nb_asteroid);
	list_asteroid[i_asteroid].x = list_asteroid[asteroid].x;
	list_asteroid[i_asteroid].y = list_asteroid[asteroid].y;
	list_asteroid[i_asteroid].speed = list_asteroid[asteroid].speed;
	list_asteroid[i_asteroid].type = list_asteroid[asteroid].type;
	list_asteroid[i_asteroid].angle = *angle + (float)(rand() % 45) - 22.5;
}