#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Player.h"

typedef bool;
#define true 1
#define false 0
#define PI 3.1415926535



int Delta(sfClock* deltaclock) {
    sfTime dtime = sfClock_getElapsedTime(deltaclock);
    int delta = sfTime_asMicroseconds(dtime);
    sfClock_restart(deltaclock);
    return delta;
}

int main() {
    //rend la console de commande invisible
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    //crée une nouvelle seed random
    srand(time(0));

    int score = 0;
    int delta;

    //création de l'écran et ses coordonnés
    sfVideoMode mode = sfVideoMode_getDesktopMode();
    int width = mode.width;
    int height = mode.height;
    sfRenderWindow* window = sfRenderWindow_create(mode, "CSFML Test", sfClose, NULL);
    sfWindow_setFramerateLimit(window, 60);

    //création du vaisseau
    struct vaisseau player = { .x = width / 2,
                               .y = height / 2,
                               .force = (sfVector2f){0,0},
                               .vitesse = 0.5,
                               .angle = -90};
    sfFont* font = sfFont_createFromFile("Arial.ttf");
    player.text = sfText_create();
    sfText_setFont(player.text, font);
    char str_player[2];
    snprintf(str_player, 2, "A");
    sfText_setString(player.text, str_player);
    sfText_setCharacterSize(player.text, width*100/1920);
    sfText_setOrigin(player.text, (sfVector2f) {sfText_getLocalBounds(player.text).width/2, sfText_getLocalBounds(player.text).height});

    //création du texte de score
    sfText* text_score = sfText_create();
    sfText_setFont(text_score, font);
    sfText_scale(text_score, (sfVector2f) { width/1920*1.5, height/1080*1.5 });

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

        Move(&player,delta);
        teleport(&player, height, width);

        sfText_setPosition(player.text, (sfVector2f) { player.x, player.y });
        sfText_setRotation(player.text,player.angle+90);

        //actualisation du score
        char str_score[15];
        snprintf(str_score, 15, "Score : %d", score);
        sfText_setString(text_score, str_score);

        //efface tout
        sfRenderWindow_clear(window, sfBlack);

        //affiche le joueur
        sfRenderWindow_drawText(window, player.text, NULL);

        //affiche le score
        sfRenderWindow_drawText(window, text_score, NULL);

        //affiche la nouvelle frame de l'écran
        sfRenderWindow_display(window);
    }

    //détruit tous les élément créé
    sfText_destroy(text_score);
    sfRenderWindow_destroy(window);
    sfClock_destroy(deltaclock);

    return 0;
}