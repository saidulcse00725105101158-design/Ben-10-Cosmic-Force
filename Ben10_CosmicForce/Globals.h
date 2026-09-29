#pragma once

GameState gameState = STATE_MENU;
bool pausedFromGame = false;

unsigned int imgMenuBg, imgBg[3], imgPlatform[3], imgHealthBar;
unsigned int imgWatch[3];
unsigned int imgFloatLvl1[2], imgFloatLvl2[2];
unsigned int imgBenStance, imgBenWalk[3], imgBenJump, imgBenCrouch, imgBenAttack[2];
unsigned int imgHeat[8], imgFireball;
unsigned int imgWildStance, imgWildRun[2], imgWildJump[3], imgWildAttack;
unsigned int imgEnemyStance, imgEnemyWalk[2], imgEnemyAttack[3], imgEnemyDead;
unsigned int imgBossStance, imgBossWalk, imgBossWalk2, imgBossJump[2], imgBossAttack[2], imgBossFire;
unsigned int imgDragon[4], imgDragonFire;
unsigned int imgMedals[3];

double platformOffset = 0;

int level = 1;
int enemiesDefeated = 0;
int score = 0;
int enemySpawnTimer = 1500;
int dragonSpawnTimer = 3000;
int medalSpawnTimer = 2000;

struct {
	int y;
	int velocityY;
	bool jumping;
	bool crouching;
	bool attacking;
	int attackTimer;
	int attackCooldown;
	int attackFrame;
	int walkFrame, walkTimer;
	bool moving;
	bool facingLeft;
	int health, maxHealth;
	int form;
	int watchSelection;
	bool transformed;
	int transformTimeLeft;
	bool cooling;
	int cooldownTimeLeft;
} player;

Enemy enemies[MAX_ENEMIES];
Boss boss;
Fireball heatFireball;
Fireball bossFireball;
Dragon dragons[MAX_DRAGONS];
Fireball dragonFireballs[MAX_DRAGONS];
Medal levelMedals[MAX_MEDALS];

int highScores[3] = { 0, 0, 0 };

Rect btnStart = { SCREEN_WIDTH / 2 - 140, 330, 280, 60 };
Rect btnResume = { SCREEN_WIDTH / 2 - 140, 400, 280, 60 };
Rect btnHigh = { SCREEN_WIDTH / 2 - 140, 260, 280, 60 };
Rect btnExit = { SCREEN_WIDTH / 2 - 140, 190, 280, 60 };
Rect btnBack = { SCREEN_WIDTH / 2 - 100, 60, 200, 55 };

bool prevE = false, prevF = false, prevEsc = false, prevSpace = false, prevJump = false, prevClickHandled = false;

char textBuf[100];