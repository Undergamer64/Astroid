#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Menu.h"

int menu_pressed = 0;

void Draw_menu1(sfWindow* window, sfText* text_menu_titre, sfText* text_menu_play, sfText* text_menu_quit) {
	sfRenderWindow_clear(window, sfBlack);

	sfRenderWindow_drawText(window, text_menu_titre, NULL);
	sfRenderWindow_drawText(window, text_menu_play, NULL);
	sfRenderWindow_drawText(window, text_menu_quit, NULL);

	sfRenderWindow_display(window);
}

void Draw_menu2(sfWindow* window, int difficulty, sfText* text_menu_difficulty, sfText* text_menu_begin, sfText* text_menu_easy, sfText* text_menu_medium, sfText* text_menu_hard){
	sfRenderWindow_clear(window, sfBlack);

	sfRenderWindow_drawText(window, text_menu_difficulty, NULL);
	sfRenderWindow_drawText(window, text_menu_begin, NULL);
	switch (difficulty) {
	case 2:
		sfRenderWindow_drawText(window, text_menu_easy, NULL);
		break;

	case 4:
		sfRenderWindow_drawText(window, text_menu_medium, NULL);
		break;

	case 6:
		sfRenderWindow_drawText(window, text_menu_hard, NULL);
		break;

	default:
		printf("ERROR DIFFICULTY");
		break;
	}

	sfRenderWindow_display(window);
}

void choice_menu1(sfWindow* window ,int* menu, sfText* text_menu_play, sfText* text_menu_quit) {
	if (sfMouse_isButtonPressed(sfMouseLeft)) {
		if (!menu_pressed) {
			menu_pressed = 1;
			int mousex = sfMouse_getPosition(window).x;
			int mousey = sfMouse_getPosition(window).y;
			sfFloatRect mouse = (sfFloatRect){ mousex,mousey,1,1 };
			sfFloatRect rectplay = sfText_getGlobalBounds(text_menu_play);
			sfFloatRect rectquit = sfText_getGlobalBounds(text_menu_quit);
			if (sfFloatRect_intersects(&rectplay, &mouse, NULL)) {
				*menu += 1;
			}
			if (sfFloatRect_intersects(&rectquit, &mouse, NULL)) {
				sfWindow_close(window);
			}
		}
	}
	else if (menu_pressed) {
		menu_pressed = 0;
	}
}

void choice_menu2(sfWindow* window, int* menu, int* difficulty, sfText* text_menu_begin, sfText* text_menu_easy, sfText* text_menu_medium, sfText* text_menu_hard) {
	if (sfMouse_isButtonPressed(sfMouseLeft)) {
		if (!menu_pressed) {
			menu_pressed = 1;
			int mousex = sfMouse_getPosition(window).x;
			int mousey = sfMouse_getPosition(window).y;
			sfFloatRect mouse = (sfFloatRect){ mousex,mousey,1,1 };
			sfFloatRect rectbegin = sfText_getGlobalBounds(text_menu_begin);
			sfFloatRect recteasy = sfText_getGlobalBounds(text_menu_easy);
			sfFloatRect rectmedium = sfText_getGlobalBounds(text_menu_medium);
			sfFloatRect recthard = sfText_getGlobalBounds(text_menu_hard);
			int dif = *difficulty;
			if (sfFloatRect_intersects(&rectbegin, &mouse, NULL)) {
				*menu = 0;
			}
			switch (dif) {
			case 2:
				if (sfFloatRect_intersects(&recteasy, &mouse, NULL)) {
					*difficulty += 2;
				}
				break;

			case 4:
				if (sfFloatRect_intersects(&rectmedium, &mouse, NULL)) {
					*difficulty += 2;
				}
				break;

			case 6:
				if (sfFloatRect_intersects(&recthard, &mouse, NULL)) {
					*difficulty = 2;
				}
				break;

			default:
				printf("ERROR DIFFICULTY");
				break;
			}
		}
	}
	else if (menu_pressed) {
		menu_pressed = 0;
	}
}