#pragma once

struct vaisseau {
    float x;
    float y;
    sfVector2f force;
    float vitesse;
    float angle;
    sfText* text;
};

void Move_player(player);

void Teleport(player, size);

void Shoot(player, list_bullet, size, nb_bullet);