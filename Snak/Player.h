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

void teleport(player, height, width);