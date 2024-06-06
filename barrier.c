#include "barrier.h"
#include <math.h>
// Initialize the barrier
void InitBarrier(Barrier *barrier, float screenWidth, float screenHeight) {
    barrier->position = (Vector2){ 0, screenHeight * 0.85f }; // Position at 85% of the screen height
    barrier->width = screenWidth;
    barrier->height = screenHeight * 0.15f; // Height is 15% of the screen height
    barrier->color = BLUE;
    barrier ->hits =0;
    barrier -> life = 8;
    barrier -> texture = LoadTexture("/Users/shafi/Documents/test/asset/layer11200x120.jpg");
}

// Draw the barrier on the screen
void DrawBarrier(Barrier *barrier) {
    DrawTexture(barrier->texture, barrier->position.x, barrier->position.y, WHITE);
}
// Check collision between EnemyBulletHB and Barrier
bool CheckCollisionEnemyBulletHBWithBarrier(Bullet *bullet, Barrier *barrier) {
    Rectangle bulletRect = { bullet->position.x, bullet->position.y, bullet->width, bullet->height };
    Rectangle barrierRect = { barrier->position.x, barrier->position.y, barrier->width, barrier->height };
    
    return CheckCollisionRecs(bulletRect, barrierRect);
}
