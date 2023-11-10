#pragma once

struct bullet {
    float x;
    float y;
    float vitesse;
    float angle;
    sfRectangleShape* shape;
};

void Create_bullet(player, list_bullet);