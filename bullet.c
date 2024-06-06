#include "bullet.h"

// Initialize the bullet
void InitBullet(Bullet *bullet, Vector2 position, Vector2 speed, Color color) {
    bullet->position = position;
    bullet->speed = speed;
    bullet->width = 5.0f;
    bullet->height = 10.0f;
    bullet->color = color;
    bullet->type = BULLET_RECTANGLE; // Set the bullet type to rectangle
    bullet->active = false;
    bullet->texture = LoadTexture("/Users/shafi/Documents/test/asset/enemy1 (1).png");
} 

// Update the bullet's position
void UpdateBullet(Bullet *bullet) {
    if (bullet->active) {
        bullet->position.y -= bullet->speed.y; // Update bullet position based on speed

        // Deactivate bullet if it goes off-screen
        if (bullet->position.y < -bullet->height) {
            bullet->active = false;
        }
    }
}

// Draw the bullet on the screen
void DrawBullet(Bullet *bullet) {
    if (bullet->active) {
        DrawRectangle(bullet->position.x, bullet->position.y, bullet->width, bullet->height, bullet->color);
    }
}

// Initialize the enemy bullet
void InitEnemyBullet(Bullet *bullet, Vector2 position, Vector2 speed, Color color) {
    bullet->position = position;
    bullet->speed = speed;
    bullet->width = 5.0f;
    bullet->height = 10.0f;
    bullet->color = color;
    bullet->active = false;
    bullet->type = BULLET_RECTANGLE; // Set the bullet type to rectangle
}

// Update the enemy bullet's position
void UpdateEnemyBullet(Bullet *bullet) {
    if (bullet->active) {
        bullet->position.y += bullet->speed.y; // Update bullet position based on speed
        bullet->position.x += bullet->speed.x;
        // Deactivate bullet if it goes off-screen
        if (bullet->position.y > GetScreenHeight() || bullet->position.y < 0 ||
            bullet->position.x > GetScreenWidth() || bullet->position.x < 0) {
            bullet->active = false;
        }
    }
}

// Draw the enemy bullet on the screen
void DrawEnemyBullet(Bullet *bullet) {
    if (bullet->active) {
        DrawRectangle(bullet->position.x, bullet->position.y, bullet->width, bullet->height, bullet->color);
    }
}

// Initialize the homing bullet
void InitEnemyBulletHB(Bullet *bullet, Vector2 position, Vector2 speed, Color color) {
    bullet->position = position;
    bullet->speed = speed;
    bullet->width = 50.0f;
    bullet->height = 25.0f;
    bullet->color = color;
    bullet->active = false;
    bullet->type = BULLET_RECTANGLE;
    bullet->texture = LoadTexture("/Users/shafi/Downloads/enemy1.png");

    if (bullet->texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load texture for HB bullet");
    } else {
        TraceLog(LOG_INFO, "Successfully loaded texture for HB bullet");
    }
}

// Update the homing bullet's position
void UpdateEnemyBulletHB(Bullet *bullet) {
    if (bullet->active) {
        bullet->position.y += bullet->speed.y; // Update bullet position based on speed

        // Deactivate bullet if it goes off-screen
        if (bullet->position.y >= GetScreenHeight()) {
            bullet->active = false;
        }
    }
}

// Draw the homing bullet on the screen
void DrawEnemyBulletHB(Bullet *bullet) {
    if (bullet->active) {
        DrawTexture(bullet->texture, bullet->position.x, bullet->position.y, WHITE);
    }
}
