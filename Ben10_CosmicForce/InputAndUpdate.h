#pragma once

void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}

void iMouse(int button, int state, int mx, int my) {
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

	if (gameState == STATE_MENU) {
		if (pausedFromGame && pointInRect(mx, my, btnResume)) {
			gameState = STATE_PLAYING;
			pausedFromGame = false;
			return;
		}
		if (!pausedFromGame && pointInRect(mx, my, btnStart)) {
			resetGame();
			gameState = STATE_PLAYING;
			mciSendString("stop menusong", NULL, 0, NULL);
			mciSendString("play gamesong repeat", NULL, 0, NULL);
			return;
		}
		if (pointInRect(mx, my, btnHigh)) {
			gameState = STATE_HIGHSCORE;
			return;
		}
		if (pointInRect(mx, my, btnExit)) exit(0);
	}
	else if (gameState == STATE_HIGHSCORE) {
		if (pointInRect(mx, my, btnBack)) gameState = STATE_MENU;
	}
	else if (gameState == STATE_GAMEOVER || gameState == STATE_VICTORY) {
		if (pointInRect(mx, my, btnBack)) {
			gameState = STATE_MENU;
			pausedFromGame = false;
			mciSendString("play menusong repeat", NULL, 0, NULL);
		}
	}
}

void updatePlayerPhysics() {
	bool moved = false;
	double scrollDelta = 0;

	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		platformOffset -= WALK_SCROLL_SPEED;
		player.facingLeft = false;
		moved = true;
		scrollDelta = -WALK_SCROLL_SPEED;
	}
	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		platformOffset += WALK_SCROLL_SPEED;
		player.facingLeft = true;
		moved = true;
		scrollDelta = WALK_SCROLL_SPEED;
	}

	player.moving = moved;

	if (moved && !player.jumping) {
		player.walkTimer += TICK_MS;
		if (player.walkTimer >= 90) {
			player.walkTimer = 0;
			player.walkFrame = (player.walkFrame + 1) % 3;
		}
	}

	if (scrollDelta != 0) {
		for (int i = 0; i < MAX_ENEMIES; i++) if (enemies[i].active) enemies[i].x += scrollDelta;
		for (int i = 0; i < MAX_DRAGONS; i++) {
			if (dragons[i].active) dragons[i].x += scrollDelta;
			if (dragonFireballs[i].active) dragonFireballs[i].x += scrollDelta;
		}
		if (boss.active) boss.x += scrollDelta;
		if (bossFireball.active) bossFireball.x += scrollDelta;
		if (heatFireball.active) heatFireball.x += scrollDelta;
	}

	bool jumpKeyNow = (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP));
	if (jumpKeyNow && !prevJump && !player.jumping) {
		player.jumping = true;
		player.velocityY = JUMP_START_VELOCITY;
	}
	prevJump = jumpKeyNow;

	int prevY = player.y;

	if (player.jumping) {
		player.y += player.velocityY;
		player.velocityY -= GRAVITY;

		int floatingTopY = 0;
		bool hasPlatform = getFloatingPlatformUnderPlayer(prevY, &floatingTopY);

		// HEAD / CEILING COLLISION FIX UNDER FLOATING PLATFORMS
		if (level == 1 || level == 2) {
			int topY = GROUND_Y + FLOATING_PLATFORM_Y_OFFSET;
			int bottomY = topY + FLOATING_PLATFORM_H;
			int startIndex = (int)floor((-platformOffset - FLOATING_PLATFORM_W) / (double)FLOATING_PLATFORM_SPACING);
			for (int i = startIndex; i < startIndex + 4; i++) {
				if (i < 0) continue;
				double screenX = i * (double)FLOATING_PLATFORM_SPACING + platformOffset;
				if (screenX > SCREEN_WIDTH) break;
				if (screenX + FLOATING_PLATFORM_W >= PLAYER_X && screenX <= PLAYER_X + PLAYER_W) {
					// Check if Ben hits the underside of the platform while moving upwards
					if (prevY + PLAYER_H <= bottomY && player.y + PLAYER_H > bottomY && player.velocityY > 0) {
						player.y = bottomY - PLAYER_H;
						player.velocityY = 0; // Stop upward movement immediately
					}
				}
			}
		}

		if (hasPlatform && player.velocityY <= 0 && prevY >= floatingTopY && player.y <= floatingTopY) {
			player.y = floatingTopY;
			player.jumping = false;
			player.velocityY = 0;
		}
		else if (player.y <= GROUND_Y) {
			player.y = GROUND_Y;
			player.jumping = false;
			player.velocityY = 0;
		}
	}
	else {
		int floatingTopY = 0;
		bool hasPlatform = getFloatingPlatformUnderPlayer(prevY, &floatingTopY);
		if (hasPlatform && player.y <= floatingTopY) {
			player.y = floatingTopY;
		}
		else {
			int supportY = hasPlatform ? floatingTopY : GROUND_Y;
			if (player.y > supportY) {
				player.jumping = true;
				player.velocityY = 0;
			}
			else {
				player.y = supportY;
			}
		}
	}

	player.crouching = (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN)) && !player.jumping;

	bool spaceNow = isKeyPressed(' ');
	if (spaceNow && !prevSpace && player.attackCooldown <= 0) doPlayerAttack();
	prevSpace = spaceNow;

	if (player.attackCooldown > 0) player.attackCooldown -= TICK_MS;
	if (player.attacking) {
		player.attackTimer -= TICK_MS;
		if (player.attackTimer <= 0) player.attacking = false;
	}
}

void updateWatch() {
	bool eNow = isKeyPressed('e');
	if (eNow && !prevE && !player.transformed && !player.cooling) {
		player.watchSelection = (player.watchSelection + 1) % 3;
		mciSendString("play watchsong from 0", NULL, 0, NULL);
	}
	prevE = eNow;

	bool fNow = isKeyPressed('f');
	if (fNow && !prevF) {
		if (!player.transformed && !player.cooling && player.watchSelection != FORM_BEN10) {
			player.form = player.watchSelection;
			player.transformed = true;
			player.transformTimeLeft = TRANSFORM_DURATION_MS;
			mciSendString("play transformsong from 0", NULL, 0, NULL);
		}
		else if (player.transformed) {
			player.transformed = false;
			player.form = FORM_BEN10;
			player.cooling = true;
			player.cooldownTimeLeft = TRANSFORM_COOLDOWN_MS;
			player.watchSelection = FORM_BEN10;
			mciSendString("play transformsong from 0", NULL, 0, NULL);
		}
	}
	prevF = fNow;

	if (player.transformed) {
		player.transformTimeLeft -= TICK_MS;
		if (player.transformTimeLeft <= 0) {
			player.transformed = false;
			player.form = FORM_BEN10;
			player.cooling = true;
			player.cooldownTimeLeft = TRANSFORM_COOLDOWN_MS;
			player.watchSelection = FORM_BEN10;
		}
	}
	else if (player.cooling) {
		player.cooldownTimeLeft -= TICK_MS;
		if (player.cooldownTimeLeft <= 0) player.cooling = false;
	}
}

void updateEnemies() {
	int speed = (level == 1) ? ENEMY_SPEED_L1 : ENEMY_SPEED_L2;
	double pCenterX = PLAYER_X + PLAYER_W / 2.0;

	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (!enemies[i].active) continue;
		double eCenterX = enemies[i].x + ENEMY_W / 2.0;
		double distToPlayer = abs(eCenterX - pCenterX);

		if (distToPlayer > ENEMY_ATTACK_RANGE) {
			if (eCenterX > pCenterX) {
				enemies[i].x -= speed;
				enemies[i].facingLeft = false;
			}
			else {
				enemies[i].x += speed;
				enemies[i].facingLeft = true;
			}
			enemies[i].attacking = false;
			enemies[i].walkTimer += TICK_MS;
			if (enemies[i].walkTimer >= 140) {
				enemies[i].walkTimer = 0;
				enemies[i].walkFrame = (enemies[i].walkFrame + 1) % 2;
			}
		}
		else {
			enemies[i].attacking = true;
			enemies[i].attackCooldown -= TICK_MS;
			if (enemies[i].attackCooldown <= 0) {
				enemies[i].attackCooldown = ENEMY_ATTACK_COOLDOWN_MS;
				if (!playerIsDodging()) {
					playerTakeDamage(enemies[i].damage);
					mciSendString("play hit from 0", NULL, 0, NULL);
				}
			}
			enemies[i].walkTimer += TICK_MS;
			if (enemies[i].walkTimer >= 160) {
				enemies[i].walkTimer = 0;
				enemies[i].walkFrame = (enemies[i].walkFrame + 1) % 3;
			}
		}

		if (enemies[i].x < -ENEMY_W - 400 || enemies[i].x > SCREEN_WIDTH + 400) {
			enemies[i].active = false;
		}
	}

	for (int i = 0; i < MAX_DRAGONS; i++) {
		if (!dragons[i].active) continue;
		double dCenterX = dragons[i].x + DRAGON_W / 2.0;
		dragons[i].facingLeft = (dCenterX > pCenterX);

		double distToPlayer = abs(dCenterX - pCenterX);
		if (distToPlayer > 350) {
			if (dCenterX > pCenterX) dragons[i].x -= 4;
			else dragons[i].x += 4;
		}

		dragons[i].walkTimer += TICK_MS;
		if (dragons[i].walkTimer >= 150) {
			dragons[i].walkTimer = 0;
			dragons[i].walkFrame = (dragons[i].walkFrame + 1) % 4;
		}

		dCenterX = dragons[i].x + DRAGON_W / 2.0;
		distToPlayer = abs(dCenterX - pCenterX);

		if (distToPlayer <= DRAGON_ATTACK_RANGE) {
			dragons[i].attackCooldown -= TICK_MS;
			if (dragons[i].attackCooldown <= 0 && !dragonFireballs[i].active) {
				dragons[i].attackCooldown = DRAGON_ATTACK_COOLDOWN_MS;
				dragonFireballs[i].active = true;
				dragonFireballs[i].x = dragons[i].facingLeft ? dragons[i].x - DRAGON_FIRE_W : dragons[i].x + DRAGON_W;
				double startY = GROUND_Y + 180 + DRAGON_H * 0.45;
				dragonFireballs[i].y = startY;
				dragonFireballs[i].velocityX = dragons[i].facingLeft ? -6.0 : 6.0;
				dragonFireballs[i].velocityY = -3.5;
			}
		}

		if (dragons[i].x < -DRAGON_W - 400 || dragons[i].x > SCREEN_WIDTH + 400) {
			dragons[i].active = false;
		}
	}

	if (level != 3) {
		enemySpawnTimer -= TICK_MS;
		if (enemySpawnTimer <= 0) {
			spawnEnemy();
			enemySpawnTimer = ENEMY_SPAWN_MIN_MS + (rand() % (ENEMY_SPAWN_MAX_MS - ENEMY_SPAWN_MIN_MS));
		}
		dragonSpawnTimer -= TICK_MS;
		if (dragonSpawnTimer <= 0) {
			spawnDragon();
			dragonSpawnTimer = 3000 + (rand() % 3000);
		}
	}

	if (level == 1 && enemiesDefeated >= ENEMIES_TO_LEVEL2) {
		level = 2;
		for (int i = 0; i < MAX_ENEMIES; i++) enemies[i].active = false;
		for (int i = 0; i < MAX_DRAGONS; i++) dragons[i].active = false;
	}
	if (level == 2 && enemiesDefeated >= ENEMIES_TO_BOSS) {
		level = 3;
		for (int i = 0; i < MAX_ENEMIES; i++) enemies[i].active = false;
		for (int i = 0; i < MAX_DRAGONS; i++) dragons[i].active = false;
		spawnBoss();
	}
}

void updateBoss() {
	if (!boss.active) return;
	double distToPlayer = boss.x - (PLAYER_X + PLAYER_W);

	if (distToPlayer > BOSS_ATTACK_RANGE) {
		boss.x -= BOSS_SPEED;
		boss.attacking = false;
		boss.walkTimer += TICK_MS;
		if (boss.walkTimer >= 150) {
			boss.walkTimer = 0;
			boss.walkFrame = (boss.walkFrame + 1) % 2;
		}
	}
	else {
		boss.attacking = true;
		boss.attackCooldown -= TICK_MS;
		if (boss.attackCooldown <= 0) {
			boss.attackCooldown = BOSS_ATTACK_COOLDOWN_MS;
			if (!playerIsDodging()) {
				playerTakeDamage(BOSS_DAMAGE);
				mciSendString("play hit from 0", NULL, 0, NULL);
			}
		}
	}
	boss.fireCooldown -= TICK_MS;
	if (boss.fireCooldown <= 0 && !bossFireball.active) {
		boss.fireCooldown = BOSS_FIRE_COOLDOWN_MS;
		bossFireball.active = true;
		bossFireball.x = boss.x;
		bossFireball.velocityX = -BOSS_FIRE_SPEED;
		bossFireball.fromBoss = true;
	}
}

void updateFireballs() {
	if (heatFireball.active) {
		heatFireball.x += heatFireball.velocityX;
		if (heatFireball.x > SCREEN_WIDTH || heatFireball.x < -FIREBALL_W) heatFireball.active = false;

		// 1. Enemy Collision Check (Ground Height)
		for (int i = 0; i < MAX_ENEMIES; i++) {
			bool inEnemyX = (heatFireball.x + FIREBALL_W >= enemies[i].x) && (heatFireball.x <= enemies[i].x + ENEMY_W);
			bool inEnemyY = (heatFireball.y + FIREBALL_H >= GROUND_Y) && (heatFireball.y <= GROUND_Y + ENEMY_H);

			if (enemies[i].active && heatFireball.active && inEnemyX && inEnemyY) {
				enemies[i].health -= PLAYER_ATTACK_DAMAGE_HEATBLAST;
				heatFireball.active = false;
				if (enemies[i].health <= 0) {
					enemies[i].active = false;
					enemiesDefeated++;
					score += 50;
				}
			}
		}

		// 2. Dragon Collision Check (Sky Height)
		for (int i = 0; i < MAX_DRAGONS; i++) {
			bool inDragonX = (heatFireball.x + FIREBALL_W >= dragons[i].x) && (heatFireball.x <= dragons[i].x + DRAGON_W);
			bool inDragonY = (heatFireball.y + FIREBALL_H >= GROUND_Y + 180) && (heatFireball.y <= GROUND_Y + 180 + DRAGON_H);

			if (dragons[i].active && heatFireball.active && inDragonX && inDragonY) {
				dragons[i].active = false;
				heatFireball.active = false;
				score += 100;
			}
		}

		// 3. Boss Collision Check (Ground Height)
		if (boss.active && heatFireball.active) {
			bool inBossX = (heatFireball.x + FIREBALL_W >= boss.x) && (heatFireball.x <= boss.x + BOSS_W);
			bool inBossY = (heatFireball.y + FIREBALL_H >= GROUND_Y) && (heatFireball.y <= GROUND_Y + BOSS_H);

			if (inBossX && inBossY) {
				boss.health -= PLAYER_ATTACK_DAMAGE_HEATBLAST;
				heatFireball.active = false;
				if (boss.health <= 0) {
					boss.active = false;
					score += 150;
					gameState = STATE_VICTORY;
					tryInsertHighScore(score);
				}
			}
		}
	}

	if (bossFireball.active) {
		bossFireball.x += bossFireball.velocityX;
		if (bossFireball.x < -BOSSFIRE_W || bossFireball.x > SCREEN_WIDTH) bossFireball.active = false;

		if (bossFireball.active && bossFireball.x <= PLAYER_X + PLAYER_W && bossFireball.x + BOSSFIRE_W >= PLAYER_X && !playerIsDodging()) {
			playerTakeDamage(BOSS_FIRE_DAMAGE);
			bossFireball.active = false;
		}
	}

	for (int i = 0; i < MAX_DRAGONS; i++) {
		if (!dragonFireballs[i].active) continue;

		dragonFireballs[i].x += dragonFireballs[i].velocityX;
		dragonFireballs[i].y += dragonFireballs[i].velocityY;

		if (dragonFireballs[i].x < -DRAGON_FIRE_W || dragonFireballs[i].x > SCREEN_WIDTH || dragonFireballs[i].y < 0 || dragonFireballs[i].y > SCREEN_HEIGHT) {
			dragonFireballs[i].active = false;
			continue;
		}

		bool collisionX = dragonFireballs[i].x <= PLAYER_X + PLAYER_W && dragonFireballs[i].x + DRAGON_FIRE_W >= PLAYER_X;
		bool collisionY = dragonFireballs[i].y <= player.y + PLAYER_H && dragonFireballs[i].y + DRAGON_FIRE_H >= player.y;

		if (collisionX && collisionY && !playerIsDodging()) {
			playerTakeDamage(DRAGON_FIRE_DAMAGE);
			dragonFireballs[i].active = false;
		}
	}
}

void fixedUpdate() {
	bool escNow = isKeyPressed(27);
	if (escNow && !prevEsc && gameState == STATE_PLAYING) {
		gameState = STATE_MENU;
		pausedFromGame = true;
	}
	prevEsc = escNow;

	if (gameState != STATE_PLAYING) return;

	updatePlayerPhysics();
	updateWatch();
	updateEnemies();
	updateBoss();
	updateFireballs();
}