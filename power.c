#include "power.h"
#include <stdio.h>
Sound popwerup ;
// Initialize the power (lifeline)
void InitPower(Power *power, int initialLifeline) {
    power->lifeline = initialLifeline;
    power->gameOver = false;
    power->invincible = false;
    power->invincibleTime = 0;
}

// Update the power (check for collisions with enemy bullets)
void UpdatePower(Power *power, Bullet *enemyBullets, int maxEnemyBullets, Player *player, float deltaTime) {
    if (power->invincible) {
        power->invincibleTime -= deltaTime;
        if (power->invincibleTime <= 0) {
            power->invincible = false;
        }
    }

    
}



