#include "raylib.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "barrier.h"
#include "level.h"
#include "astroid.h"
#include "power.h"
#include "unwantedaesteroids.h"
#include "raygui.h"

// Define game screen dimensions
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define MAX_BULLETS 10
#define MAX_ENEMY_BULLETS 10
#define MAX_FRAMES 200
#define NUM_ASTEROIDS 3

bool paused = false;
float frameTime = 0.0f; // Initialize frame time
float frameSpeed = 0.05f; // Set the speed of frame change
int currentFrame = 0; // Initialize the current frame index

void InitializeGame(Player *player, Bullet bullets[], Bullet enemyBullets[], Bullet h2bomb[], Enemy *enemy, Astroid *comet, Power *power, UnwantedAsteroid asteroids[], Barrier *barrier, Level *level, Music *backgroundMusic, Texture2D frames[]) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MySpaceGame");

    // Load the background image
    char filename[256];
    for (int i = 0; i < MAX_FRAMES; i++) {
        sprintf(filename, "/Users/shafi/Documents/test/asset/spacespritebackground/output_%03d.png", i + 1);
        frames[i] = LoadTexture(filename);
    }

    InitAudioDevice(); // Initialize audio device
    *backgroundMusic = LoadMusicStream("/Users/shafi/Documents/test/asset/battle-march-action-loop-6935.mp3"); // Load music file
    PlayMusicStream(*backgroundMusic); // Start playing the music

    // Initialize the player
    InitPlayer(player, (Vector2){ SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT - 200 }, 50.0f, 70.0f, 5.0f, RED);

    // Initialize bullets array
    for (int i = 0; i < MAX_BULLETS; i++) {
        float startX = player->position.x + player->width / 2;
        InitBullet(&bullets[i], (Vector2){ startX, player->position.y }, (Vector2){ 0, 10 }, RED);
    }

    // Initialize the enemy
    InitEnemy(enemy, (Vector2){ SCREEN_WIDTH / 2 - 25, 10 }, 50.0f, 50.0f, 10.0f, BLUE);
    enemy->ufoexplotion = LoadSound("/Users/shafi/Documents/test/asset/UFOexplosion2.mp3");

    // Initialize enemy bullets array
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        InitEnemyBullet(&enemyBullets[i], (Vector2){ 0, 0 }, (Vector2){ 0, 5 }, BLUE);
    }

    // Initialize enemy homing bullets
    InitEnemyBulletHB(&h2bomb[0], (Vector2){ SCREEN_WIDTH / 2, 0 }, (Vector2){ 0, 5 }, PURPLE);

    // Initialize comet
    InitAsteroid(comet, (Vector2){ 100, 50 }, 30.0f, GRAY);

    // Initialize power
    InitPower(power, 5); // Initial lifeline is 5
    power->powerup = LoadSound("/Users/shafi/Documents/test/asset/Power-up receiving.mp3");

    // Initialize unwanted comet
    for (int i = 0; i < NUM_ASTEROIDS; i++) {
        InitUnwantedAsteroid(&asteroids[i], i);
    }

    // Initialize the barrier
    InitBarrier(barrier, SCREEN_WIDTH, SCREEN_HEIGHT * 0.15);

    // Initialize the level
    InitLevel(level);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
}

void UpdateGame(Player *player, Bullet bullets[], Bullet enemyBullets[], Bullet h2bomb[], Enemy *enemy, Astroid *comet, Power *power, UnwantedAsteroid asteroids[], Barrier *barrier, Level *level, Music backgroundMusic) {
    frameTime += GetFrameTime();

    if (frameTime >= frameSpeed) {
        currentFrame++;
        currentFrame %= MAX_FRAMES;
        frameTime = 0;
    }

    if (IsKeyPressed(KEY_P)) {
        paused = !paused;
    }

    if (!paused) {
        if (!power->gameOver && barrier->life > 0) {
            UpdateMusicStream(backgroundMusic); // Update the music stream
            UpdatePlayer(player, bullets, MAX_BULLETS); // Update player position based on user input
            UpdateEnemy(enemy, GetFrameTime(), h2bomb); // Update enemy position
            EnemyShoot(enemy, enemyBullets, MAX_ENEMY_BULLETS, player); // Enemy shooting logic

            // Update power (check for collisions with enemy bullets)
            UpdatePower(power, enemyBullets, MAX_ENEMY_BULLETS, player, GetFrameTime());

            // Update comet
            UpdateAsteroid(comet, GetFrameTime(), player, bullets, MAX_BULLETS, power);

            // Update level (check for collisions and update score)
            UpdateLevel(level, bullets, enemyBullets, h2bomb, MAX_BULLETS, enemy, power, player, barrier);

            for (int i = 0; i < NUM_ASTEROIDS; i++) {
                UpdateUnwantedAsteroid(&asteroids[i], GetFrameTime(), player, bullets, MAX_BULLETS, NULL);
            }
        }
    }
}

void DrawGame(Player *player, Bullet bullets[], Bullet enemyBullets[], Bullet h2bomb[], Enemy *enemy, Astroid *comet, Power *power, UnwantedAsteroid asteroids[], Barrier *barrier, Level *level, Texture2D frames[]) {
    BeginDrawing();
    ClearBackground(RAYWHITE); // Clear the background with white

    // Draw the current frame
    DrawTexture(frames[currentFrame], 0, 0, WHITE);
    DrawPlayer(player); // Draw the player

    // Draw bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        DrawBullet(&bullets[i]);
    }

    // Draw enemy
    DrawEnemy(enemy);

    // Draw enemy bullets
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        DrawEnemyBullet(&enemyBullets[i]);
    }

    // Draw the h2 bomb
    DrawEnemyBulletHB(&h2bomb[0]);

    // Draw comet
    DrawAsteroid(comet);

    // Draw unwanted asteroids
    for (int i = 0; i < NUM_ASTEROIDS; i++) {
        DrawUnwantedAsteroid(&asteroids[i]);
    }

    // Draw the barrier
    DrawBarrier(barrier);

    // Draw the level (display score)
    DrawLevel(level, power, barrier);

    if (paused) {
        DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 20, 40, GRAY);
    }

    EndDrawing();
}

int main(void) {
    // Define game objects and assets
    Player player;
    Bullet bullets[MAX_BULLETS];
    Bullet enemyBullets[MAX_ENEMY_BULLETS];
    Bullet h2bomb[1];
    Enemy enemy;
    Astroid comet;
    Power power;
    UnwantedAsteroid asteroids[NUM_ASTEROIDS];
    Barrier barrier;
    Level level;
    Music backgroundMusic;
    Texture2D frames[MAX_FRAMES];

    // Initialize the game
    InitializeGame(&player, bullets, enemyBullets, h2bomb, &enemy, &comet, &power, asteroids, &barrier, &level, &backgroundMusic, frames);

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        UpdateGame(&player, bullets, enemyBullets, h2bomb, &enemy, &comet, &power, asteroids, &barrier, &level, backgroundMusic); // Update game state
        DrawGame(&player, bullets, enemyBullets, h2bomb, &enemy, &comet, &power, asteroids, &barrier, &level, frames); // Draw game state
    }

    // De-initialization
    for (int i = 0; i < MAX_FRAMES; i++) {
        UnloadTexture(frames[i]); // Unload textures
    }

    UnloadMusicStream(backgroundMusic); // Unload music stream
    CloseAudioDevice(); // Close the audio device
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

