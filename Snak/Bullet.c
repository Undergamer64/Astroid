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

int speed_bullet = 15;

void Create_bullet(struct vaisseau player, struct bullet list_bullet[], int size[], int nb_bullet) {
	for (int i = 0; i < nb_bullet; i++) {
		if (!list_bullet[i].is_visible) {
			//creation de nouvelle balle
			list_bullet[i].x = player.x;
			list_bullet[i].y = player.y;
			list_bullet[i].angle = player.angle;
			list_bullet[i].speed = speed_bullet;
			list_bullet[i].is_visible = 1;
			sfClock_restart(list_bullet[i].lifetime);
			sfRectangleShape_setSize(list_bullet[i].shape, (sfVector2f) { size[0] * 15 / 1920, size[0] * 15 / 1920 });
			sfRectangleShape_setOrigin(list_bullet[i].shape, (sfVector2f) { size[0] * 7.5 / 1920, size[0] * 7.5 / 1920 });
			sfRectangleShape_setRotation(list_bullet[i].shape, list_bullet[i].angle);
			sfRectangleShape_setPosition(list_bullet[i].shape, (sfVector2f) { list_bullet[i].x, list_bullet[i].y });
			break;
		}
	}
}

void Move_bullets(struct bullet list_bullet[], int nb_bullet, int delta) {
	for (int i = 0; i < nb_bullet; i++) {
		if (list_bullet[i].is_visible) {
			float dirx = cos(list_bullet[i].angle * PI / 180);
			float diry = sin(list_bullet[i].angle * PI / 180);

			list_bullet[i].x += list_bullet[i].speed * dirx * delta / 10000;
			list_bullet[i].y += list_bullet[i].speed * diry * delta / 10000;
			
			if (sfTime_asMicroseconds(sfClock_getElapsedTime(list_bullet[i].lifetime)) >= ((sfVideoMode_getDesktopMode().height/2) / speed_bullet)*10000) {
				list_bullet[i].is_visible = 0;
			}
		}
		sfRectangleShape_setPosition(list_bullet[i].shape, (sfVector2f) { list_bullet[i].x, list_bullet[i].y });
	}
}

void Collision_bullets(struct bullet list_bullet[], int nb_bullet, struct asteroid list_asteroid[], int nb_asteroid, int size[], int *score) {
	for (int i = 0; i < nb_bullet; i++) {
		if (list_bullet[i].is_visible == 0) {
			continue;
		}
		for (int j = 0; j < nb_asteroid; j++) {
			if (list_asteroid[j].type == 0) {
				continue;
			}
			float dist_x = fabs(list_asteroid[j].x - list_bullet[i].x);
			float dist_y = fabs(list_asteroid[j].y - list_bullet[i].y);
			float dist = sqrtf(dist_x * dist_x + dist_y * dist_y);
			
			if (dist <= ((float)list_asteroid[i].type * 20.0f) + ((float)size[0] * 15.0f / 1920.0f)/2.0f) {
				float angle = list_asteroid[j].angle;
				list_bullet[i].is_visible = 0;
 				*score += 100;
				Division(list_asteroid, j, angle, nb_asteroid);
				break; 
			}
		}
	}
}