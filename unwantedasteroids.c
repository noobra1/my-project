
#include "raylib.h"
#include "player.h"
#include "bullet.h"
#include "power.h"
#include <stdlib.h>
#include <time.h>
#include "unwantedaesteroids.h"

#define NUM_ASTEROID_TYPES 3

void InitUnwantedAsteroid(UnwantedAsteroid *asteroid, int type) {
    asteroid->type = type;
    asteroid->active = false;
    srand(time(NULL)); // Initialize random seed

    switch (type) {
        case 0: // rock1
            asteroid->radius = 20.0f;
            asteroid->color = GRAY;
            asteroid->speed = 100.0f;
            asteroid->spawnInterval = 3.0f;
            break;
        case 1: // rock2
            asteroid->radius = 30.0f;
            asteroid->color = RED;
            asteroid->speed = 150.0f;
            asteroid->spawnInterval = 5.0f;
            break;
        case 2: // Reserved for the third asteroid
            asteroid->radius = 40.0f;
            asteroid->color = ORANGE;
            asteroid->speed = 200.0f;
            asteroid->spawnInterval = 7.0f;
            break;
    }
    asteroid->timeSinceSpawn = 0.0f;
}

void UpdateUnwantedAsteroid(UnwantedAsteroid *asteroid, float deltaTime, Player *player, Bullet *bullets, int maxBullets, Power *power) {
    asteroid->timeSinceSpawn += deltaTime;
    if (!asteroid->active && asteroid->timeSinceSpawn >= asteroid->spawnInterval) {
        asteroid->active = true;
        if (asteroid->type == 0) { // rock1
            asteroid->position.x = rand() % GetScreenWidth();
            asteroid->position.y = -asteroid->radius;
        } else if (asteroid->type == 1) { // rock2
            asteroid->position.x = (rand() % 2 == 0) ? -asteroid->radius : GetScreenWidth() + asteroid->radius;
            asteroid->position.y = rand() % GetScreenHeight();
            asteroid->direction = (asteroid->position.x < 0) ? 1 : -1; // Determine the direction
        }
        asteroid->timeSinceSpawn = 0.0f;
    }

    if (asteroid->active) {
        if (asteroid->type == 0) { // rock1
            asteroid->position.y += asteroid->speed * deltaTime;
        } else if (asteroid->type == 1) { // rock2
            asteroid->position.x += asteroid->direction * asteroid->speed * deltaTime;
        }

        // Collision with player and bullets (simplified for demonstration)
        if (CheckCollisionCircles(asteroid->position, asteroid->radius, player->position, player->width / 2)) {
            asteroid->active = false;
        }

        for (int i = 0; i < maxBullets; i++) {
            if (bullets[i].active && CheckCollisionCircleRec(asteroid->position, asteroid->radius, (Rectangle){ bullets[i].position.x, bullets[i].position.y, bullets[i].width, bullets[i].height })) {
                bullets[i].active = false;
                asteroid->active = false;
            }
        }

        if (asteroid->type == 0 && asteroid->position.y > GetScreenHeight() + asteroid->radius) {
            asteroid->active = false;
        } else if (asteroid->type == 1 && (asteroid->position.x > GetScreenWidth() + asteroid->radius || asteroid->position.x < -asteroid->radius)) {
            asteroid->active = false;
        }
    }
}

void DrawUnwantedAsteroid(UnwantedAsteroid *asteroid) {
    if (asteroid->active) {
        DrawCircleV(asteroid->position, asteroid->radius, asteroid->color);
    }
}
