#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Menu.h"

typedef bool;
#define true 1
#define false 0
#define PI 3.1415926535
#define nb_bullet 6
#define nb_asteroid 80

int Delta(sfClock* deltaclock) {
    sfTime dtime = sfClock_getElapsedTime(deltaclock);
    int delta = sfTime_asMicroseconds(dtime);
    sfClock_restart(deltaclock);
    return delta;
}

void Draw_game(sfWindow* window, int score, sfText* text_score, struct Ship player, struct bullet list_bullet[], struct asteroid list_asteroid[], int size[]) {
    char str_score[20];
    snprintf(str_score, 20, "Score : %d", score);
    sfText_setString(text_score, str_score);
    
    //efface tout
    sfRenderWindow_clear(window, sfBlack);

    //affiche le joueur
    sfRenderWindow_drawText(window, player.text, NULL);

    //affiche les balles
    for (int i = 0; i < nb_bullet; i++) {
        if (list_bullet[i].is_visible) {
            sfRenderWindow_drawRectangleShape(window, list_bullet[i].shape, NULL);
        }
    }

    for (int i = 0; i < nb_asteroid; i++) {
        if (list_asteroid[i].type > 0) {
            sfRenderWindow_drawCircleShape(window, list_asteroid[i].shape, NULL);
        }
    }

    //affiche le score
    sfRenderWindow_drawText(window, text_score, NULL);

    //affiche la nouvelle frame de l'écran
    sfRenderWindow_display(window);
}

int main() {
    //rend la console de commande invisible
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    //crée une nouvelle seed random
    srand(time(0));

    int score = 0;
    int delta;
    int difficulty = 2;
    int wave = 0;
    int menu = 1;

    //création de l'écran et ses coordonnés
    sfVideoMode mode = sfVideoMode_getDesktopMode();
    int size[2] = {mode.width, mode.height};
    sfRenderWindow* window = sfRenderWindow_create(mode, "CSFML Test", sfClose, NULL);
    sfWindow_setFramerateLimit(window, 60);

    //création du vaisseau
    struct Ship player = { .x = size[0] / 2,
                               .y = size[1] / 2,
                               .force = (sfVector2f){0,0},
                               .speed = size[1]/4320.0,
                               .angle = -90};
    sfFont* font = sfFont_createFromFile("Arial.ttf");
    player.text = sfText_create();
    sfText_setFont(player.text, font);
    sfText_setString(player.text, "A");
    sfText_setCharacterSize(player.text, size[0]*100/1920);
    sfText_setOrigin(player.text, (sfVector2f) {sfText_getLocalBounds(player.text).width/2, sfText_getLocalBounds(player.text).height});

    //création d'un liste de balle
    struct bullet list_bullet[nb_bullet];

    for (int i = 0; i < nb_bullet; i++) {
        list_bullet[i].is_visible = 0;
        list_bullet[i].shape = sfRectangleShape_create();
        list_bullet[i].lifetime = sfClock_create();
    }
    

    struct asteroid list_asteroid[nb_asteroid];

    for (int i = 0; i < nb_asteroid; i++) {
        list_asteroid[i].type = 0;
        list_asteroid[i].shape = sfCircleShape_create();
        sfCircleShape_setFillColor(list_asteroid[i].shape, sfColor_fromRGB(127,127,127));
    }


    //creation of all texte int the game
    sfText* text_score = sfText_create();
    sfText_setFont(text_score, font);
    sfText_scale(text_score, (sfVector2f) { size[0]/1920*1.5, size[1]/1080*1.5 });

    sfText* text_menu_titre = sfText_create();
    sfText_setString(text_menu_titre, "Astroid");
    sfText_setFont(text_menu_titre, font);
    sfText_scale(text_menu_titre, (sfVector2f) { size[0] / 1920 * 3.0, size[0] / 1920 * 3.0 });
    sfText_setOrigin(text_menu_titre, (sfVector2f) { sfText_getLocalBounds(text_menu_titre).width / 2, sfText_getLocalBounds(text_menu_titre).height });
    sfText_setPosition(text_menu_titre, (sfVector2f) { size[0] / 2, (size[1] / 8) * 1 });
    
    sfText* text_menu_play = sfText_create();
    sfText_setString(text_menu_play, "Play");
    sfText_setFont(text_menu_play, font);
    sfText_scale(text_menu_play, (sfVector2f) { size[0] / 1920 * 2.0, size[0] / 1920 * 2.0 });
    sfText_setOrigin(text_menu_play, (sfVector2f) { sfText_getLocalBounds(text_menu_play).width / 2, sfText_getLocalBounds(text_menu_play).height });
    sfText_setPosition(text_menu_play, (sfVector2f) { size[0] / 2, (size[1] / 8) * 5});

    sfText* text_menu_quit = sfText_create();
    sfText_setString(text_menu_quit, "Quit");
    sfText_setFont(text_menu_quit, font);
    sfText_scale(text_menu_quit, (sfVector2f) { size[0] / 1920 * 2.0, size[0] / 1920 * 2.0 });
    sfText_setOrigin(text_menu_quit, (sfVector2f) { sfText_getLocalBounds(text_menu_quit).width / 2, sfText_getLocalBounds(text_menu_quit).height });
    sfText_setPosition(text_menu_quit, (sfVector2f) { size[0] / 2, (size[1] / 8) * 7 });

    sfText* text_menu_difficulty = sfText_create();
    sfText_setString(text_menu_difficulty, "Choose a difficulty");
    sfText_setFont(text_menu_difficulty, font);
    sfText_scale(text_menu_difficulty, (sfVector2f) { size[0] / 1920 * 3.0, size[0] / 1920 * 3.0 });
    sfText_setOrigin(text_menu_difficulty, (sfVector2f) { sfText_getLocalBounds(text_menu_difficulty).width / 2, sfText_getLocalBounds(text_menu_difficulty).height });
    sfText_setPosition(text_menu_difficulty, (sfVector2f) { size[0] / 2, (size[1] / 8) * 1 });

    sfText* text_menu_easy = sfText_create();
    sfText_setString(text_menu_easy, "EASY");
    sfText_setFont(text_menu_easy, font);
    sfText_setFillColor(text_menu_easy, sfGreen);
    sfText_scale(text_menu_easy, (sfVector2f) { size[0] / 1920 * 2.0, size[0] / 1920 * 2.0 });
    sfText_setOrigin(text_menu_easy, (sfVector2f) { sfText_getLocalBounds(text_menu_easy).width / 2, sfText_getLocalBounds(text_menu_easy).height});
    sfText_setPosition(text_menu_easy, (sfVector2f) { size[0] / 2, (size[1] / 8) * 5 });

    sfText* text_menu_medium = sfText_create();
    sfText_setString(text_menu_medium, "MEDIUM");
    sfText_setFont(text_menu_medium, font);
    sfText_setFillColor(text_menu_medium, sfYellow);
    sfText_scale(text_menu_medium, (sfVector2f) { size[0] / 1920 * 2.0, size[0] / 1920 * 2.0 });
    sfText_setOrigin(text_menu_medium, (sfVector2f) { sfText_getLocalBounds(text_menu_medium).width / 2, sfText_getLocalBounds(text_menu_medium).height });
    sfText_setPosition(text_menu_medium, (sfVector2f) { size[0] / 2, (size[1] / 8) * 5 });

    sfText* text_menu_hard = sfText_create();
    sfText_setString(text_menu_hard, "HARD");
    sfText_setFont(text_menu_hard, font);
    sfText_setFillColor(text_menu_hard, sfRed);
    sfText_scale(text_menu_hard, (sfVector2f) { size[0] / 1920 * 2.0, size[0] / 1920 * 2.0 });
    sfText_setOrigin(text_menu_hard, (sfVector2f) { sfText_getLocalBounds(text_menu_hard).width / 2, sfText_getLocalBounds(text_menu_hard).height });
    sfText_setPosition(text_menu_hard, (sfVector2f) { size[0] / 2, (size[1] / 8) * 5 });

    sfText* text_menu_begin = sfText_create();
    sfText_setString(text_menu_begin, "Begin");
    sfText_setFont(text_menu_begin, font);
    sfText_scale(text_menu_begin, (sfVector2f) { size[0] / 1920 * 2.0, size[0] / 1920 * 2.0 });
    sfText_setOrigin(text_menu_begin, (sfVector2f) { sfText_getLocalBounds(text_menu_begin).width / 2, sfText_getLocalBounds(text_menu_begin).height });
    sfText_setPosition(text_menu_begin, (sfVector2f) { size[0] / 2, (size[1] / 8) * 7 });

    //création des clocks
    sfClock* deltaclock = sfClock_create();

    //tant que la fentre est ouvert
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            //si une fenêtre est fermer ou que echape est appuyer
            if (event.type == sfEvtClosed || (event.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeyEscape)))
                //ferme le jeu
                sfRenderWindow_close(window);
        }

        delta = Delta(deltaclock);

        switch (menu) {
        case 0:
            Move_player(&player, delta, size);
            Teleport_player(&player, size);

            Shoot(&player, list_bullet, size, nb_bullet);
            Move_bullets(list_bullet, nb_bullet, delta);

            if (Are_all_dead(list_asteroid, nb_asteroid)) {
                Create_asteroid(list_asteroid, nb_asteroid, size, difficulty, &wave);
            }
            Move_asteroid(list_asteroid, nb_asteroid, delta, size);
            Teleport_asteroid(list_asteroid, nb_asteroid, size, delta);

            Collision_bullets(list_bullet, nb_bullet, list_asteroid, nb_asteroid, player, size, &score);
            Collision_joueur(&player, list_asteroid, nb_asteroid, size);

            Draw_game(window, score, text_score, player, list_bullet, list_asteroid, size);
            break;
        
        case 1:
            Draw_menu1(window, text_menu_titre, text_menu_play, text_menu_quit);
            choice_menu1(window, &menu, text_menu_play, text_menu_quit);
            break;

        case 2:
            Draw_menu2(window, difficulty, text_menu_difficulty, text_menu_begin, text_menu_easy, text_menu_medium, text_menu_hard);
            choice_menu2(window, &menu, &difficulty, text_menu_begin, text_menu_easy, text_menu_medium, text_menu_hard);
            break;

        default :
            printf("ERROR MENU");
            break;
        }
    }

    //détruit tous les élément créé
    for (int i = 0; i < nb_bullet; i++) {
        sfRectangleShape_destroy(list_bullet[i].shape);
        sfClock_destroy(list_bullet[i].lifetime);
    }
    for (int i = 0; i < nb_asteroid; i++) {
        sfCircleShape_destroy(list_asteroid[i].shape);
    }
    sfText_destroy(text_score);
    sfText_destroy(text_menu_titre);
    sfText_destroy(text_menu_play);
    sfText_destroy(text_menu_quit);
    sfText_destroy(text_menu_difficulty);
    sfText_destroy(text_menu_easy);
    sfText_destroy(text_menu_medium);
    sfText_destroy(text_menu_hard);
    sfText_destroy(text_menu_begin);
    sfRenderWindow_destroy(window);
    sfClock_destroy(deltaclock);

    return 0;
}
