#include "player.h" // Include bullet.h for bullet functionality
#include <math.h>
#include<stdio.h>
// Initialize the player
void InitPlayer(Player *player, Vector2 startPosition, float width, float height, float speed, Color color) {
    player->position = startPosition;
    player->width = width;
    player->height = height;
    player->speed = speed;
    player->color = color;
    player->texture = LoadTexture("/Users/shafi/Documents/test/asset/ship1.png");
}

// Update the player's position based on user input
void UpdatePlayer(Player *player, Bullet *bullets, int maxBullets) {
    if (IsKeyDown(KEY_RIGHT)) player->position.x += player->speed;
    if (IsKeyDown(KEY_LEFT)) player->position.x -= player->speed;
    if (IsKeyDown(KEY_UP)) player->position.y -= player->speed;
    if (IsKeyDown(KEY_DOWN)) player->position.y += player->speed;

    // Prevent player from moving out of bounds
    if (player->position.x < 0) player->position.x = 0;
    if (player->position.x > GetScreenWidth() - player->width) player->position.x = GetScreenWidth() - player->width;

    // Shoot bullets
    if (IsKeyDown(KEY_SPACE)) {
        for (int i = 0; i < maxBullets; i++) {
            if (!bullets[i].active) {
                bullets[i].position = (Vector2){ player->position.x + player->width / 2, player->position.y };
                bullets[i].active = true;
                break; // Exit loop after shooting a bullet
            }
        }
    }
    // Update bullets
    for (int i = 0; i < maxBullets; i++) {
        UpdateBullet(&bullets[i]);
    }
}
// Draw the player on the screen
void DrawPlayer(Player *player) {
    if (player->invincible) {
        // Draw the player as a blue dotted circle when invincible
        for (int i = 0; i < 360; i += 20) {
            Vector2 dotPosition = {
                player->position.x + player->width / 2 + cosf(DEG2RAD * i) * player->width / 2,
                player->position.y + player->height / 2 + sinf(DEG2RAD * i) * player->height / 2
            };
            DrawCircleV(dotPosition, 5, BLUE);
        }
    }
        // Draw the player as a rectangle
       else{ 
        DrawTexture(player->texture, player->position.x, player->position.y, WHITE);
       
       }
}
