#ifndef UNWANTEDASTEROIDS_H
#define UNWANTEDASTEROIDS_H

#include "raylib.h"
#include "player.h"
#include "bullet.h"
#include "power.h"

typedef struct UnwantedAsteroid {
    Vector2 position;
    float radius;
    Color color;
    bool active;
    int type;
    float speed;
    float timeSinceSpawn;
    float spawnInterval;
    int direction; // Only used for rock2 to determine movement direction
    Texture2D texture;
} UnwantedAsteroid;

void InitUnwantedAsteroid(UnwantedAsteroid *asteroid, int type);
void UpdateUnwantedAsteroid(UnwantedAsteroid *asteroid, float deltaTime, Player *player, Bullet *bullets, int maxBullets, Power *power);
void DrawUnwantedAsteroid(UnwantedAsteroid *asteroid);

#endif
