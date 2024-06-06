#ifndef POWER_H
#define POWER_H

#include "raylib.h"
#include "bullet.h"
#include "player.h"
#include "barrier.h"

typedef struct Power {
    int lifeline;
    bool gameOver;
    bool invincible;      // Invincibility status
    float invincibleTime; // Invincibility duration
    Sound powerup;
} Power;

void InitPower(Power *power, int initialLifeline);
void UpdatePower(Power *power, Bullet *enemyBullets, int maxEnemyBullets, Player *player, float deltaTime);


#endif // POWER_H
