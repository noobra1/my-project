#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include "time.h"
typedef enum {
    BULLET_RECTANGLE,
    BULLET_CIRCLE
} BulletType;

typedef struct {
    Vector2 position;
    Vector2 speed;
    float width;
    float height;
    float radius;
    Color color;
    bool active;
    BulletType type;
    Texture2D texture;
} Bullet;
// Bullet
void InitBullet(Bullet *bullet, Vector2 position, Vector2 speed, Color color);
void UpdateBullet(Bullet *bullet);
void DrawBullet(Bullet *bullet);

//  enemyBullet
void InitEnemyBullet(Bullet *bullet, Vector2 position, Vector2 speed, Color color);
void UpdateEnemyBullet(Bullet *bullet);
void DrawEnemyBullet(Bullet *bullet);

// EnemyBulletHB
void InitEnemyBulletHB(Bullet *bullet, Vector2 position, Vector2 speed, Color color);
void UpdateEnemyBulletHB(Bullet *bullet);
void DrawEnemyBulletHB(Bullet *bullet);

#endif // BULLET_H

