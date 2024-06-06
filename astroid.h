#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"
#include "player.h"
#include "bullet.h"
#include "power.h"


typedef struct {
    Vector2 position;
    float radius;
    Color color;
    bool active;
    Texture2D texture;
} Astroid;

void InitAsteroid(Astroid *asteroid, Vector2 position, float radius, Color color);
void UpdateAsteroid(Astroid *asteroid, float deltaTime, Player *player, Bullet *bullets, int maxBullets, Power *power) ;
void DrawAsteroid(Astroid *asteroid);

#endif // ASTEROID_H
