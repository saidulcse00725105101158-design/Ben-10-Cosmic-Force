
#pragma once

enum GameState { STATE_MENU, STATE_PLAYING, STATE_HIGHSCORE, STATE_GAMEOVER, STATE_VICTORY };
enum AlienForm { FORM_BEN10 = 0, FORM_HEATBLAST = 1, FORM_WILDMUTT = 2 };

struct Rect { int x, y, w, h; };

struct Enemy {
	bool active;
	double x;
	int health;
	int damage;
	int walkFrame, walkTimer;
	bool attacking;
	int attackTimer;
	int attackCooldown;
	bool facingLeft;
};

struct Boss {
	bool active;
	double x;
	int health;
	int walkFrame, walkTimer;
	bool attacking;
	int attackTimer;
	int attackCooldown;
	int fireCooldown;
};

struct Fireball {
	bool active;
	double x;
	double y;
	double velocityX;
	double velocityY;
	bool fromBoss;
};

struct Dragon {
	bool active;
	double x;
	int walkFrame, walkTimer;
	int attackCooldown;
	bool facingLeft;
};

struct Medal {
	bool active;
	double x;
	double y;
	int type;
};