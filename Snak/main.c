#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Player.h"
#include "Bullet.h"

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

void Draw(sfWindow* window, int score, sfText* text_score,struct vaisseau player,struct bullet list_bullet[], int nb_bullet) {
    //actualisation du score
    char str_score[15];
    snprintf(str_score, 15, "Score : %d", score);
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
    int nb_bullet = 6;

    //création de l'écran et ses coordonnés
    sfVideoMode mode = sfVideoMode_getDesktopMode();
    int size[2] = {mode.width, mode.height};
    sfRenderWindow* window = sfRenderWindow_create(mode, "CSFML Test", sfClose, NULL);
    sfWindow_setFramerateLimit(window, 60);

    //création du vaisseau
    struct vaisseau player = { .x = size[0] / 2,
                               .y = size[1] / 2,
                               .force = (sfVector2f){0,0},
                               .vitesse = size[0]/4320.0,
                               .angle = -90};
    sfFont* font = sfFont_createFromFile("Arial.ttf");
    player.text = sfText_create();
    sfText_setFont(player.text, font);
    sfText_setString(player.text, "A");
    sfText_setCharacterSize(player.text, size[0]*100/1920);
    sfText_setOrigin(player.text, (sfVector2f) {sfText_getLocalBounds(player.text).width/2, sfText_getLocalBounds(player.text).height});

    //création d'un liste de balle
    struct bullet list_bullet[6];

    for (int i = 0; i < nb_bullet; i++) {
        list_bullet[i].is_visible = 0;
        list_bullet[i].shape = sfRectangleShape_create();
        list_bullet[i].lifetime = sfClock_create();
    }
    
    //création du texte de score
    sfText* text_score = sfText_create();
    sfText_setFont(text_score, font);
    sfText_scale(text_score, (sfVector2f) { size[0]/1920*1.5, size[1]/1080*1.5 });

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

        Move_player(&player,delta,size);
        Teleport(&player, size);

        Shoot(&player, list_bullet, size, nb_bullet);
        Move_bullets(list_bullet, nb_bullet, delta);
        
        Draw(window, score, text_score, player, list_bullet, nb_bullet);
    }

    //détruit tous les élément créé
    for (int i = 0; i < nb_bullet; i++) {
        sfRectangleShape_destroy(list_bullet[i].shape);
        sfClock_destroy(list_bullet[i].lifetime);
    }

    sfText_destroy(text_score);
    sfRenderWindow_destroy(window);
    sfClock_destroy(deltaclock);

    return 0;
}
