#pragma once

void drawMenu() {
	iShowImage(0, 0, MENUBG_W, MENUBG_H, imgMenuBg);
	iSetColor(0, 0, 0);
	iFilledRectangle(SCREEN_WIDTH / 2 - 260, SCREEN_HEIGHT - 130, 520, 80);
	iSetColor(255, 220, 0);
	iTextTTF(SCREEN_WIDTH / 2 - 230, SCREEN_HEIGHT - 95, "BEN 10 : COSMIC FORCE", 24);

	if (pausedFromGame) {
		drawButton(btnResume, "RESUME", 40, 140, 40);
		drawButton(btnHigh, "HIGH SCORES", 40, 90, 200);
		drawButton(btnExit, "EXIT", 180, 40, 40);
	}
	else {
		drawButton(btnStart, "START GAME", 40, 140, 40);
		drawButton(btnHigh, "HIGH SCORES", 40, 90, 200);
		drawButton(btnExit, "EXIT", 180, 40, 40);
	}
}

void drawHighScore() {
	iShowImage(0, 0, MENUBG_W, MENUBG_H, imgMenuBg);
	iSetColor(0, 0, 0);
	iFilledRectangle(SCREEN_WIDTH / 2 - 220, 150, 440, 300);
	iSetColor(255, 220, 0);
	iTextTTF(SCREEN_WIDTH / 2 - 90, 410, "HIGH SCORES", 24);

	iSetColor(255, 255, 255);

	iShowImage(SCREEN_WIDTH / 2 - 130, 332, 30, 30, imgMedals[0]);
	sprintf(textBuf, "1st : %d", highScores[0]);
	iTextTTF(SCREEN_WIDTH / 2 - 80, 340, textBuf, 18);

	iShowImage(SCREEN_WIDTH / 2 - 130, 282, 30, 30, imgMedals[1]);
	sprintf(textBuf, "2nd : %d", highScores[1]);
	iTextTTF(SCREEN_WIDTH / 2 - 80, 290, textBuf, 18);

	iShowImage(SCREEN_WIDTH / 2 - 130, 232, 30, 30, imgMedals[2]);
	sprintf(textBuf, "3rd : %d", highScores[2]);
	iTextTTF(SCREEN_WIDTH / 2 - 80, 240, textBuf, 18);

	drawButton(btnBack, "BACK", 90, 90, 90);
}

void drawPlatform() {
	unsigned int tex = imgPlatform[level - 1];
	int offset = ((int)platformOffset) % PLATFORM_TILE_W;
	if (offset > 0) offset -= PLATFORM_TILE_W;
	for (int x = offset; x < SCREEN_WIDTH; x += PLATFORM_TILE_W) {
		iShowImage(x, PLATFORM_Y, PLATFORM_TILE_W, PLATFORM_TILE_H, tex);
	}
}

bool getFloatingPlatformUnderPlayer(int referenceY, int *outTopY) {
	if (level != 1 && level != 2) return false;
	int topY = GROUND_Y + FLOATING_PLATFORM_Y_OFFSET;
	if (topY > referenceY) return false;

	int startIndex = (int)floor((-platformOffset - FLOATING_PLATFORM_W) / (double)FLOATING_PLATFORM_SPACING);
	for (int i = startIndex; i < startIndex + 4; i++) {
		if (i < 0) continue;
		double screenX = i * (double)FLOATING_PLATFORM_SPACING + platformOffset;
		if (screenX > SCREEN_WIDTH) break;
		if (screenX + FLOATING_PLATFORM_W >= PLAYER_X && screenX <= PLAYER_X + PLAYER_W) {
			if (outTopY) *outTopY = topY;
			return true;
		}
	}
	return false;
}

void drawFloatingPlatforms() {
	if (level != 1 && level != 2) return;
	unsigned int *imgs = (level == 1) ? imgFloatLvl1 : imgFloatLvl2;
	int topY = GROUND_Y + FLOATING_PLATFORM_Y_OFFSET;
	int startIndex = (int)floor((-platformOffset - FLOATING_PLATFORM_W) / (double)FLOATING_PLATFORM_SPACING);

	for (int i = startIndex; i < startIndex + 4; i++) {
		if (i < 0) continue;
		double screenX = i * (double)FLOATING_PLATFORM_SPACING + platformOffset;
		if (screenX > SCREEN_WIDTH) break;
		unsigned int tex = imgs[((i % 2) + 2) % 2];
		iShowImage((int)screenX, topY, FLOATING_PLATFORM_W, FLOATING_PLATFORM_H, tex);
	}
}

void drawPlayer() {
	int drawY = player.y;
	int w = PLAYER_W, h = PLAYER_H;
	unsigned int tex;

	if (player.form == FORM_HEATBLAST) {
		w = HEATBLAST_W; h = HEATBLAST_H;
		if (player.attacking) tex = imgHeat[4 + (player.attackFrame % 4)];
		else if (player.jumping) tex = imgHeat[2];
		else if (player.moving) tex = imgHeat[player.walkFrame % 4];
		else tex = imgHeat[0];
	}
	else if (player.form == FORM_WILDMUTT) {
		w = WILDMUTT_W; h = WILDMUTT_H;
		if (player.attacking) tex = imgWildAttack;
		else if (player.jumping) tex = imgWildJump[player.walkFrame % 3];
		else if (player.moving) tex = imgWildRun[player.walkFrame % 2];
		else tex = imgWildStance;
	}
	else {
		w = PLAYER_W; h = player.crouching ? PLAYER_CROUCH_H : PLAYER_H;
		if (player.attacking) tex = imgBenAttack[player.attackFrame];
		else if (player.jumping) tex = imgBenJump;
		else if (player.crouching) tex = imgBenCrouch;
		else if (player.moving) tex = imgBenWalk[player.walkFrame % 3];
		else tex = imgBenStance;
	}
	iShowImageFlip(PLAYER_X, drawY, w, h, tex, player.facingLeft);
}

void drawEnemies() {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (!enemies[i].active) continue;
		unsigned int tex;
		if (enemies[i].attacking) tex = imgEnemyAttack[enemies[i].walkFrame % 3];
		else tex = imgEnemyWalk[enemies[i].walkFrame % 2];
		iShowImageFlip((int)enemies[i].x, GROUND_Y, ENEMY_W, ENEMY_H, tex, enemies[i].facingLeft);
	}
}

void drawDragons() {
	for (int i = 0; i < MAX_DRAGONS; i++) {
		if (!dragons[i].active) continue;
		unsigned int tex = imgDragon[dragons[i].walkFrame % 4];
		iShowImageFlip((int)dragons[i].x, GROUND_Y + 180, DRAGON_W, DRAGON_H, tex, dragons[i].facingLeft);
	}
}

void drawBoss() {
	if (!boss.active) return;
	unsigned int tex;
	if (boss.attacking) tex = imgBossAttack[boss.walkFrame % 2];
	else tex = (boss.walkFrame % 2 == 0) ? imgBossWalk : imgBossWalk2;
	iShowImage((int)boss.x, GROUND_Y, BOSS_W, BOSS_H, tex);
}

void drawFireballs() {
	if (heatFireball.active) {
		iShowImageFlip((int)heatFireball.x, (int)heatFireball.y, FIREBALL_W, FIREBALL_H, imgFireball, heatFireball.velocityX < 0);
	}
	if (bossFireball.active) iShowImage((int)bossFireball.x, GROUND_Y + BOSS_H / 3, BOSSFIRE_W, BOSSFIRE_H, imgBossFire);

	for (int i = 0; i < MAX_DRAGONS; i++) {
		if (dragonFireballs[i].active) {
			iShowImageFlip((int)dragonFireballs[i].x, (int)dragonFireballs[i].y, DRAGON_FIRE_W, DRAGON_FIRE_H, imgDragonFire, dragonFireballs[i].velocityX < 0);
		}
	}
}

void drawHUD() {
	double healthFrac = (double)player.health / (double)player.maxHealth;
	if (healthFrac < 0) healthFrac = 0;

	iSetColor(200, 30, 30);
	iFilledRectangle(HEALTHBAR_X + 860, HEALTHBAR_Y + 63, (int)((HEALTHBAR_W - 90) * healthFrac), 28);
	iShowImage(HEALTHBAR_X, HEALTHBAR_Y, HEALTHBAR_W, HEALTHBAR_H, imgHealthBar);

	iSetColor(255, 255, 255);
	sprintf(textBuf, "%d%%", (int)(healthFrac * 100));
	iTextTTF(HEALTHBAR_X + 860, HEALTHBAR_Y + 68, textBuf, 24);
	iTextTTF(HEALTHBAR_X + 861, HEALTHBAR_Y + 69, textBuf, 24);
	iTextTTF(HEALTHBAR_X + 859, HEALTHBAR_Y + 67, textBuf, 24);

	sprintf(textBuf, "SCORE : %d", score);
	iTextTTF(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 40, textBuf, 18);
	sprintf(textBuf, "LEVEL : %d", level);
	iTextTTF(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 65, textBuf, 18);

	iShowImage(WATCH_X, WATCH_Y, WATCH_W, WATCH_H, imgWatch[player.watchSelection]);

	if (player.cooling) {
		sprintf(textBuf, "OMNITRIX COOLDOWN : %d s", player.cooldownTimeLeft / 1000 + 1);
		iSetColor(255, 80, 80);
		iTextTTF(SCREEN_WIDTH / 2 - 110, 40, textBuf, 18);
	}
	else if (player.transformed) {
		sprintf(textBuf, "TRANSFORMED : %d s left", player.transformTimeLeft / 1000 + 1);
		iSetColor(80, 255, 120);
		iTextTTF(SCREEN_WIDTH / 2 - 100, 40, textBuf, 18);
	}
	else {
		iSetColor(255, 255, 255);
		iTextTTF(SCREEN_WIDTH / 2 - 190, 40, "E: choose alien   F: transform   SPACE: attack", 18);
	}
}

void drawGame() {
	iShowImage(0, 0, LEVELBG_W, LEVELBG_H, imgBg[level - 1]);
	drawPlatform();
	drawFloatingPlatforms();
	drawEnemies();
	drawDragons();
	drawBoss();
	drawFireballs();
	drawPlayer();
	drawHUD();
}

void drawGameOver() {
	drawGame();
	iSetColor(0, 0, 0);
	iFilledRectangle(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 100, 440, 200);
	iSetColor(220, 30, 30);
	iTextTTF(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 40, "GAME OVER", 24);
	iSetColor(255, 255, 255);
	sprintf(textBuf, "FINAL SCORE : %d", score);
	iTextTTF(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 - 10, textBuf, 18);
	drawButton(btnBack, "MAIN MENU", 90, 90, 90);
}

void drawVictory() {
	drawGame();
	iSetColor(0, 0, 0);
	iFilledRectangle(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 100, 440, 200);
	iSetColor(255, 220, 0);
	iTextTTF(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 40, "YOU WIN !", 24);
	iSetColor(255, 255, 255);
	sprintf(textBuf, "FINAL SCORE : %d", score);
	iTextTTF(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 - 10, textBuf, 18);
	drawButton(btnBack, "MAIN MENU", 90, 90, 90);
}

void iDraw() {
	iClear();
	switch (gameState) {
	case STATE_MENU:      drawMenu();      break;
	case STATE_PLAYING:   drawGame();      break;
	case STATE_HIGHSCORE: drawHighScore(); break;
	case STATE_GAMEOVER:  drawGameOver();  break;
	case STATE_VICTORY:   drawVictory();   break;
	}
}