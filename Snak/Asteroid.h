#pragma once

struct asteroid {
    float x;
    float y;
    float speed;
    float angle;
    int type;
    sfCircleShape* shape;
};

int First_slot(list_asteroid, nb_asteroid);

int Are_all_dead(list_asteroid, nb_asteroid);

void Teleport_asteroid(list_asteroid, nb_asteroid, size, delta);

void Move_asteroid(list_asteroid, nb_asteroid, delta, size);

void Create_asteroid(list_asteroid, nb_asteroid, size);

void Division(list_asteroid, asteroid, angle, nb_asteroid);