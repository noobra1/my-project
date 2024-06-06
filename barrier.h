#ifndef BARRIER_H
#define BARRIER_H

#include "raylib.h"
#include "bullet.h"

typedef struct {
    Vector2 position;
    float width;
    float height;
    int hits;
    Color color;
    int life;
    Texture2D texture;
} Barrier;

void InitBarrier(Barrier *barrier, float screenWidth, float screenHeight);
void DrawBarrier(Barrier *barrier);
bool CheckCollisionEnemyBulletHBWithBarrier(Bullet *bullet, Barrier *barrier);

#endif // BARRIER_H

