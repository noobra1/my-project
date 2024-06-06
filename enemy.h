#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "bullet.h"
#include "power.h"
#include "player.h"

typedef struct {
    Vector2 position;
    float width;
    float height;
    float speed;
    Color color;
    float amplitude;  // Amplitude of the sine wave
    float frequency;  // Frequency of the sine wave
    float phaseShift; // Phase shift of the sine wave
    float respawnTimer;
    bool active;
    float time;
    Sound ufoexplotion;
    Texture2D texture;
} Enemy;

void InitEnemy(Enemy *enemy, Vector2 startPosition, float width, float height, float speed, Color color);
void UpdateEnemy(Enemy *enemy,float deltaTime ,Bullet *bullets);
void DrawEnemy(Enemy *enemy);
void EnemyShoot(Enemy *enemy, Bullet *bullets, int maxBullets ,  Player *player);
void RespawnEnemy(Enemy *enemy, float screenWidth);


#endif // ENEMY_H
