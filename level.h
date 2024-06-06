#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "stdio.h"
#include "power.h"
#include "player.h"

typedef struct {
    int score;
} Level;

void InitLevel(Level *level);
void UpdateLevel(Level *level, Bullet *bullets,Bullet *enemyBullets ,Bullet *h2bomb ,int maxBullets, Enemy *enemy ,Power *power , Player *player ,Barrier *barrier);
void DrawLevel(Level *level,Power *power , Barrier *barrier);


#endif // LEVEL_H
