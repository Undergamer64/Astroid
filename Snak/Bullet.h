#pragma once

struct bullet {
    float x;
    float y;
    float vitesse;
    float angle;
    int is_visible;
    sfRectangleShape* shape;
};

void Create_bullet(player, list_bullet, size, nb_bullet);

void Move_bullets(list_bullet, nb_bullet, delta);