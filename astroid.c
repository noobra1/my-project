#include "astroid.h"
#include "player.h"
#include "bullet.h"
#include "power.h"
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()

static double timeSinceStart = 0;

// Initialize an asteroid
void InitAsteroid(Astroid *asteroid, Vector2 position, float radius, Color color) {
    asteroid->position = position;
    asteroid->radius = radius;
    asteroid->color = color;
    asteroid -> texture = LoadTexture("/Users/shafi/Documents/test/asset/powerup2.png");
    asteroid->active = false; // Initially inactive
    srand(time(NULL)); // Initialize random seed
}

// Update asteroid
void UpdateAsteroid(Astroid *asteroid, float deltaTime, Player *player, Bullet *bullets, int maxBullets, Power *power) {
    timeSinceStart += deltaTime;
    if (!asteroid->active && timeSinceStart >= 3) { // Check every 3 seconds
        asteroid->active = true;
        asteroid->position.x = rand() % GetScreenWidth(); // Set a random x position
        asteroid->position.y = -asteroid->radius; // Reset the position to start from the top
        timeSinceStart = 0; // Reset the timer
    }

    if (asteroid->active) {
        // Move the asteroid downwards
        asteroid->position.y += 200 * deltaTime; // Adjust the speed as needed
        if (power->invincible == false){
            player->invincible =false;
        }

        // Check for collision with player
        if (CheckCollisionCircles(asteroid->position, asteroid->radius, player->position, player->width / 2)) {
            // Activate invincibility power
            power->invincible = true;
            player->invincible = true;
            PlaySound(power->powerup);
            power->invincibleTime = 5.0f;// Power lasts for 5 seconds
            asteroid->active = false; // Deactivate the asteroid
        }

        // Check for collisions with bullets
        for (int i = 0; i < maxBullets; i++) {
            if (bullets[i].active && CheckCollisionCircleRec(asteroid->position, asteroid->radius, (Rectangle){ bullets[i].position.x, bullets[i].position.y, bullets[i].width, bullets[i].height })){
                bullets[i].active = false; // Deactivate bullet
                asteroid->active = false; // Deactivate the asteroid
                // Apply any other effects if necessary
            }
        }

        // Deactivate asteroid if it goes off-screen
        if (asteroid->position.y > GetScreenHeight() + asteroid->radius) {
            asteroid->active = false;
        }
    }
}

// Draw the asteroid
void DrawAsteroid(Astroid *asteroid) {
    if (asteroid->active) {
         DrawTextureEx(asteroid->texture, (Vector2){ asteroid->position.x - asteroid->radius, asteroid->position.y - asteroid->radius }, 0.0f, 2 * asteroid->radius / asteroid->texture.width, WHITE);
    }
}
