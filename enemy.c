#include "enemy.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

// Initialize the enemy
void InitEnemy(Enemy *enemy, Vector2 position, float width, float height, float speed, Color color) {
    enemy->position = position;
    enemy->width = width;
    enemy->height = height;
    enemy->speed = speed;
    enemy->color = color;
    enemy->active = true;
    enemy->texture = LoadTexture("/Users/shafi/Documents/test/asset/ufotrans.png");
    srand(time(NULL)); // Initialize random seed
    enemy->amplitude = 300.0f; // Fixed amplitude
    enemy->frequency = 5.0f; // Fixed frequency
    enemy->phaseShift = 0.0f; // Fixed phase shift
    enemy->time = 0.0f; // Initialize time parameter to zero
}

// Update the enemy's position
void UpdateEnemy(Enemy *enemy, float deltaTime,Bullet *h2bomb) {
    if (!enemy->active) {
        enemy->respawnTimer += deltaTime;
        if (enemy->respawnTimer >= 2.0f) { // Check if 2 seconds have passed
            RespawnEnemy(enemy, GetScreenWidth());
            enemy->respawnTimer = 0.0f; // Reset respawn timer
        }
        return;
    }
    // Update time based on deltaTime
    enemy->time += deltaTime;

    // Calculate the new position using a sine function for x and cosine for y
    float newX = enemy->amplitude * sinf(enemy->frequency * enemy->time + DEG2RAD * enemy->phaseShift);
    float newY = enemy->amplitude * cosf(enemy->frequency * enemy->time + DEG2RAD * enemy->phaseShift);

    // Update the enemy's position
    enemy->position.x += newX * deltaTime;
    enemy->position.y += newY * deltaTime;

    // Ensure the enemy stays within screen bounds by reversing direction if hitting an edge
    if(enemy->position.x < 2)
    {
        enemy->position.x += 10;
        enemy->phaseShift += 180;
    }
    
    if ( enemy->position.x >= GetScreenWidth() - enemy->width - 20) {
         enemy->position.x -= 10;
         enemy->phaseShift += 180; // Reverse direction
    }

    // Reverse direction if the enemy has reached 40% of the screen height from the top
    float lowerThreshold = GetScreenHeight() * 0.2f; // 40% of the screen height
    if (enemy->position.y >= lowerThreshold) {
        enemy->phaseShift += 180; 
        enemy->position.y -= 10; // Reverse direction
    }

    // Wrap enemy around if it goes off-screen vertically
    if (enemy->position.y <= 2) {
        enemy->phaseShift += 180;
        enemy->position.y += 10; // Reverse direction
    }
    static float timer = 0.0f; // Static variable to keep track of elapsed time
    static float fireInterval = 0.0f; // Static variable to store the fire interval

    // Generate a new random fire interval if it's the first run or if the bullet was just fired
    if (fireInterval == 0.0f || !h2bomb->active) {
        fireInterval = GetRandomValue(8, 15); // Randomly generated time interval between 8 and 15 seconds
    }
    if(!h2bomb ->active){
        timer += GetFrameTime();
        if (timer >= fireInterval) {
                if (!h2bomb[0].active) {
                    h2bomb[0].position = (Vector2){ enemy->position.x + enemy->width / 2, enemy->position.y };
                    h2bomb[0].active = true;
                    timer = 0.0f;
                    h2bomb->speed = (Vector2){ 0, 5.0f }; // Set the speed of the h2 bomb
                    fireInterval = 0.0f; // Reset the fire interval to generate a new random value next time
            }
                }
    }
    // Update h2bomb
    UpdateEnemyBulletHB(&h2bomb[0]);
}


// Draw the enemy on the screen
void DrawEnemy(Enemy *enemy) {
    if (enemy->active) {
        DrawTexture(enemy->texture, enemy->position.x, enemy->position.y, WHITE);
    }
}

// Enemy shooting logic
void EnemyShoot(Enemy *enemy, Bullet *bullets, int maxBullets, Player *player) {
    if (enemy->active && (rand() % 60) == 0) { // Enemy shoots randomly
        for (int i = 0; i < maxBullets; i++) {
            if (!bullets[i].active) {
                bullets[i].position = (Vector2){ enemy->position.x + enemy->width / 2 - bullets[i].width / 2, enemy->position.y + enemy->height };
                
                // Calculate direction to the player
                Vector2 direction = (Vector2){ player->position.x - bullets[i].position.x, player->position.y - bullets[i].position.y };
                float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
                direction.x /= length;
                direction.y /= length;

                // Set the bullet speed towards the player
                float speed = 5.0f; // Adjust bullet speed as needed
                bullets[i].speed = (Vector2){ direction.x * speed, direction.y * speed };

                bullets[i].active = true;
                break;
            }
        }
    }

    // Update enemy bullets
    for (int i = 0; i < maxBullets; i++) {
        UpdateEnemyBullet(&bullets[i]);
    }
}
// h2bomb  

// Respawn the enemy at a random position
void RespawnEnemy(Enemy *enemy, float screenWidth ) {
    enemy->position = (Vector2){ rand() % (int)(screenWidth - enemy->width), 0 };
    enemy->active = true;
}
