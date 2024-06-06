// Initialize the level
#include "level.h"

void InitLevel(Level *level) {
    level->score = 0;
}

// Update the level (check collisions, update score)
void UpdateLevel(Level *level, Bullet *bullets,Bullet *enemyBullets,Bullet *h2bomb, int maxBullets, Enemy *enemy ,Power *power ,Player *player ,Barrier *barrier) {
    for (int i = 0; i < maxBullets; i++) {
        if (bullets[i].active) {
            if (CheckCollisionRecs((Rectangle){ bullets[i].position.x, bullets[i].position.y, bullets[i].width, bullets[i].height },
                                   (Rectangle){ enemy->position.x, enemy->position.y, enemy->width, enemy->height })) {
                level->score++;
                bullets[i].active = false; // Deactivate bullet
                enemy->active = false; // Deactivate enemy
                PlaySound(enemy->ufoexplotion);//ufo explotoion sound
                 // Increase score
            
            }
        }
    }
    if(!power->invincible) {
        for (int i = 0; i < 10; i++) {
            if (enemyBullets[i].active) {
                if (CheckCollisionRecs((Rectangle){ enemyBullets[i].position.x, enemyBullets[i].position.y, enemyBullets[i].width, enemyBullets[i].height },
                                       (Rectangle){ player->position.x, player->position.y, player->width, player->height })) {
                    enemyBullets[i].active = false; // Deactivate enemy bullet
                    power->lifeline--; // Decrease lifeline
                    printf("Lifeline hit! New lifeline: %d\n", power->lifeline); // Debug print

                    if (power->lifeline <= 0) {
                        power->gameOver = true; // Set game over if lifeline is 0 or less
                        printf("Game Over!\n"); // Debug print
                    }
                }
            }
        }
    }
    if(h2bomb[0].active){ 
        if (CheckCollisionEnemyBulletHBWithBarrier(h2bomb, barrier)) {
            h2bomb[0].active = false;
            barrier ->life --;
        }
    }
    for (int i = 0; i < maxBullets; i++) {
        if (bullets[i].active) {
        if(CheckCollisionRecs((Rectangle){ bullets[i].position.x, bullets[i].position.y, bullets[i].width, bullets[i].height },
                            (Rectangle){ h2bomb[0].position.x, h2bomb[0].position.y, h2bomb->width, h2bomb->height })){
                                h2bomb[0].active = false;
    }
    }
}
}
// Draw the level (display score)
void DrawLevel(Level *level ,Power *power , Barrier *barrier) {
    // Draw the score in the top right corner
    char scoreText[20],lifelineText[20];
    sprintf(scoreText, "Score: %d", level->score);
    int textWidth = MeasureText(scoreText, 20);
    DrawText(scoreText, GetScreenWidth() - textWidth - 10, 10, 20, YELLOW);
    sprintf(lifelineText, "Lifeline: %d", power->lifeline);
    DrawText(lifelineText, 10, 10, 20, RED);
    if (power->gameOver || barrier ->life <=0) {
        const char* lostText = "You Lost";
        int lostTextWidth = MeasureText(lostText, 40);
        DrawText(lostText, GetScreenWidth() / 2 - lostTextWidth / 2, GetScreenHeight() / 2 - 20, 40, RED);
    }
    if (power->invincible) {
        DrawText("Invincible!", 10, 30, 20, GREEN);
    }

}