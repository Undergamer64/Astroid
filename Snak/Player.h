#pragma once

struct vaisseau {
    float x;
    float y;
    sfVector2f force;
    float vitesse;
    float angle;
    sfText* text;
};

void Move(player);

void Teleport(player, height, width);

void Shoot(player, list_bullet);