#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "bullet.h"
// Define player structure
typedef struct Player {
    Vector2 position;
    float width;
    float height;
    float speed;
    bool invincible;
    Color color;
    Texture2D texture;
} Player;

// Function prototypes
void InitPlayer(Player *player, Vector2 startPosition, float width, float height, float speed, Color color);
void UpdatePlayer(Player *player, Bullet *bullets, int maxBullets);
void DrawPlayer(Player *player );

#endif // PLAYER_H
