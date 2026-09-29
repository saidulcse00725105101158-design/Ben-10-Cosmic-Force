
#pragma once

void resetGame() {
	level = STARTING_LEVEL;
	enemiesDefeated = 0;
	score = 0;
	platformOffset = 0;

	enemySpawnTimer = 1500;
	dragonSpawnTimer = 1000;

	player.y = GROUND_Y;
	player.velocityY = 0;
	player.jumping = false;
	player.crouching = false;
	player.attacking = false;
	player.attackTimer = 0;
	player.attackCooldown = 0;
	player.attackFrame = 0;
	player.walkFrame = 0;
	player.walkTimer = 0;
	player.moving = false;
	player.facingLeft = false;

	player.maxHealth = 115;
	player.health = player.maxHealth;
	player.form = FORM_BEN10;
	player.watchSelection = FORM_BEN10;
	player.transformed = false;
	player.transformTimeLeft = 0;
	player.cooling = false;
	player.cooldownTimeLeft = 0;

	for (int i = 0; i < MAX_ENEMIES; i++) enemies[i].active = false;
	for (int i = 0; i < MAX_DRAGONS; i++) {
		dragons[i].active = false;
		dragonFireballs[i].active = false;
	}

	boss.active = false;
	heatFireball.active = false;
	bossFireball.active = false;
}

void spawnEnemy() {
	if (level == 3) return;
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (!enemies[i].active) {
			enemies[i].active = true;
			enemies[i].x = SCREEN_WIDTH + 20;
			enemies[i].health = ENEMY_MAX_HEALTH;
			enemies[i].damage = (level == 1) ? ENEMY_DAMAGE_L1 : ENEMY_DAMAGE_L2;
			enemies[i].walkFrame = 0;
			enemies[i].walkTimer = 0;
			enemies[i].attacking = false;
			enemies[i].attackTimer = 0;
			enemies[i].attackCooldown = 0;
			enemies[i].facingLeft = true;
			return;
		}
	}
}

void spawnDragon() {
	if (level == 3) return;
	for (int i = 0; i < MAX_DRAGONS; i++) {
		if (!dragons[i].active) {
			dragons[i].active = true;
			dragons[i].x = SCREEN_WIDTH + 50;
			dragons[i].walkFrame = 0;
			dragons[i].walkTimer = 0;
			dragons[i].attackCooldown = DRAGON_ATTACK_COOLDOWN_MS;
			dragons[i].facingLeft = true;
			return;
		}
	}
}

void spawnBoss() {
	boss.active = true;
	boss.x = SCREEN_WIDTH + 30;
	boss.health = BOSS_MAX_HEALTH;
	boss.walkFrame = 0;
	boss.walkTimer = 0;
	boss.attacking = false;
	boss.attackTimer = 0;
	boss.attackCooldown = 0;
	boss.fireCooldown = BOSS_FIRE_COOLDOWN_MS;
}

int currentAttackDamage() {
	if (player.form == FORM_HEATBLAST) return PLAYER_ATTACK_DAMAGE_HEATBLAST;
	if (player.form == FORM_WILDMUTT)  return PLAYER_ATTACK_DAMAGE_WILDMUTT;
	return PLAYER_ATTACK_DAMAGE_BEN10;
}

void doPlayerAttack() {
	player.attacking = true;
	player.attackTimer = ATTACK_ANIM_MS;
	player.attackCooldown = ATTACK_COOLDOWN_MS;
	player.attackFrame = 1 - player.attackFrame;
	mciSendString("play hit from 0", NULL, 0, NULL);

	int dmg = currentAttackDamage();

	if (player.form == FORM_HEATBLAST) {
		heatFireball.active = true;
		heatFireball.x = player.facingLeft ? PLAYER_X - FIREBALL_W : PLAYER_X + PLAYER_W;
		heatFireball.y = player.y + (HEATBLAST_H / 2) - (FIREBALL_H / 2); 
		heatFireball.velocityX = player.facingLeft ? -12 : 12;
		heatFireball.velocityX = player.facingLeft ? -12 : 12;
		heatFireball.velocityY = 0;
		heatFireball.fromBoss = false;
		return;
	}

	// Robust attack range check for normal enemies
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].active) {
			bool inRange = false;
			if (!player.facingLeft) {
				inRange = (enemies[i].x <= PLAYER_X + PLAYER_W + ATTACK_RANGE) && (enemies[i].x + ENEMY_W >= PLAYER_X + PLAYER_W);
			}
			else {
				inRange = (enemies[i].x <= PLAYER_X) && (enemies[i].x + ENEMY_W >= PLAYER_X - ATTACK_RANGE);
			}

			if (inRange) {
				enemies[i].health -= dmg;
				if (enemies[i].health <= 0) {
					enemies[i].active = false;
					enemiesDefeated++;
					score += 10;
				}
			}
		}
	}

	// Boss attack check
	if (boss.active) {
		bool bossInRange = false;
		if (!player.facingLeft) {
			bossInRange = (boss.x <= PLAYER_X + PLAYER_W + ATTACK_RANGE) && (boss.x + BOSS_W >= PLAYER_X + PLAYER_W);
		}
		else {
			bossInRange = (boss.x <= PLAYER_X) && (boss.x + BOSS_W >= PLAYER_X - ATTACK_RANGE);
		}

		if (bossInRange) {
			boss.health -= dmg;
			if (boss.health <= 0) {
				boss.active = false;
				score += 150;
				gameState = STATE_VICTORY;
				tryInsertHighScore(score);
				mciSendString("stop gamesong", NULL, 0, NULL);
				mciSendString("play winsong from 0", NULL, 0, NULL);
			}
		}
	}
}

bool playerIsDodging() { return player.jumping || player.crouching; }

void playerTakeDamage(int dmg) {
	if (gameState != STATE_PLAYING) return;
	player.health -= dmg;
	if (player.health <= 0) {
		player.health = 0;
		gameState = STATE_GAMEOVER;
		tryInsertHighScore(score);
		mciSendString("stop gamesong", NULL, 0, NULL);
		mciSendString("play gameoversong from 0", NULL, 0, NULL);
	}
}