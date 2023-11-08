#pragma once

struct vaisseau {
    float x;
    float y;
    float vitesse;
    float acceleration;
    float angle;
    sfText* text;
};

void Move();