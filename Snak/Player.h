#pragma once

struct vaisseau {
    float x;
    float y;
    sfVector2f force;
    float speed;
    float angle;
    sfText* text;
};

void Move_player(player, delta, size);

void Teleport_player(player, size);

void Shoot(player, list_bullet, size, nb_bullet);