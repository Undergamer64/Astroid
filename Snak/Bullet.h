#pragma once

struct bullet {
    float x;
    float y;
    float speed;
    float angle;
    int is_visible;
    sfClock* lifetime;
    sfRectangleShape* shape;
};

void Create_bullet(player, list_bullet, size, nb_bullet);

void Move_bullets(list_bullet, nb_bullet, delta);

void Collision_bullets(list_bullet, nb_bullet, list_asteroid, nb_asteroid, player, size, score);