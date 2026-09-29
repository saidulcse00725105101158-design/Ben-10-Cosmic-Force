#pragma once

void loadAllImages() {
	imgMenuBg = iLoadImage("images/background/main_menu_background .jpeg");
	imgBg[0] = iLoadImage("images/background/bg1.jpeg");
	imgBg[1] = iLoadImage("images/background/bg2 .jpeg");
	imgBg[2] = iLoadImage("images/background/bg3.jpeg");

	imgPlatform[0] = iLoadImage("images/foreground platform/platform.png");
	imgPlatform[1] = iLoadImage("images/foreground platform/platform_2.png");
	imgPlatform[2] = iLoadImage("images/foreground platform/platform_3.png");

	imgFloatLvl1[0] = iLoadImage("images/foreground platform/floating_platform_level1_1.png");
	imgFloatLvl1[1] = iLoadImage("images/foreground platform/floating_platform_level1_2.png");
	imgFloatLvl2[0] = iLoadImage("images/foreground platform/floating_platform_level2_1.png");
	imgFloatLvl2[1] = iLoadImage("images/foreground platform/floating_platform_level2_2.png");

	imgHealthBar = iLoadImage("images/health_bar/health_bar.png");
	imgWatch[0] = iLoadImage("images/watch/watch_default.png");
	imgWatch[1] = iLoadImage("images/watch/watch_heatblast.png");
	imgWatch[2] = iLoadImage("images/watch/watch_wildmouth.png");

	imgBenStance = iLoadImage("images/character/ben_10/ben_10_stance.png");
	imgBenWalk[0] = iLoadImage("images/character/ben_10/ben_10_walk1.png");
	imgBenWalk[1] = iLoadImage("images/character/ben_10/ben_10_walk2.png");
	imgBenWalk[2] = iLoadImage("images/character/ben_10/ben_10_walk3.png");
	imgBenJump = iLoadImage("images/character/ben_10/ben_10_jump1.png");
	imgBenCrouch = iLoadImage("images/character/ben_10/ben_10_crouch.png");
	imgBenAttack[0] = iLoadImage("images/character/ben_10/ben_10_attack1.png");
	imgBenAttack[1] = iLoadImage("images/character/ben_10/ben_10_attack2.png");

	imgHeat[0] = iLoadImage("images/character/heatblast/heatblast1.png");
	imgHeat[1] = iLoadImage("images/character/heatblast/heatblast2.png");
	imgHeat[2] = iLoadImage("images/character/heatblast/heatblast3.png");
	imgHeat[3] = iLoadImage("images/character/heatblast/heatblast4.png");
	imgHeat[4] = iLoadImage("images/character/heatblast/heatblast5.png");
	imgHeat[5] = iLoadImage("images/character/heatblast/heatblast6.png");
	imgHeat[6] = iLoadImage("images/character/heatblast/heatblast7.png");
	imgHeat[7] = iLoadImage("images/character/heatblast/heatblast8.png");
	imgFireball = iLoadImage("images/character/heatblast/yellowfireball1.png");

	imgWildStance = iLoadImage("images/character/wildmouth/wildmouth_stance.png");
	imgWildRun[0] = iLoadImage("images/character/wildmouth/wildmouth_run_1.png");
	imgWildRun[1] = iLoadImage("images/character/wildmouth/wildmouth_run2.png");
	imgWildJump[0] = iLoadImage("images/character/wildmouth/wildmouth_jump1.png");
	imgWildJump[1] = iLoadImage("images/character/wildmouth/wildmout_jump_2.png");
	imgWildJump[2] = iLoadImage("images/character/wildmouth/wildmouth_jump_3.png");
	imgWildAttack = iLoadImage("images/character/wildmouth/wildmouth_attack.png");

	imgEnemyStance = iLoadImage("images/enemy/wave1_and_wave_2/enemy_stance.png");
	imgEnemyWalk[0] = iLoadImage("images/enemy/wave1_and_wave_2/enemy_walk1.png");
	imgEnemyWalk[1] = iLoadImage("images/enemy/wave1_and_wave_2/enemy_walk2.png");
	imgEnemyAttack[0] = iLoadImage("images/enemy/wave1_and_wave_2/enemy_attack_1.png");
	imgEnemyAttack[1] = iLoadImage("images/enemy/wave1_and_wave_2/enemy_attack_2.png");
	imgEnemyAttack[2] = iLoadImage("images/enemy/wave1_and_wave_2/enemy_attack_3.png");
	imgEnemyDead = iLoadImage("images/enemy/wave1_and_wave_2/enemy_dead.png");

	imgBossStance = iLoadImage("images/enemy/Bigboss/boss_stance.png");
	imgBossWalk = iLoadImage("images/enemy/Bigboss/boss_walk_1.png");
	imgBossWalk2 = iLoadImage("images/enemy/Bigboss/boss_walk_2.png");
	imgBossJump[0] = iLoadImage("images/enemy/Bigboss/boss_jump_1.png");
	imgBossJump[1] = iLoadImage("images/enemy/Bigboss/boss_jump_2.png");
	imgBossAttack[0] = iLoadImage("images/enemy/Bigboss/boss_attack_1.png");
	imgBossAttack[1] = iLoadImage("images/enemy/Bigboss/boss_attack_2.png");
	imgBossFire = iLoadImage("images/enemy/Bigboss/boss_fire.png");

	imgDragon[0] = iLoadImage("images/enemy/wave1_and_wave_2/Dragon 1.png");
	imgDragon[1] = iLoadImage("images/enemy/wave1_and_wave_2/Dragon 2.png");
	imgDragon[2] = iLoadImage("images/enemy/wave1_and_wave_2/Dragon 3.png");
	imgDragon[3] = iLoadImage("images/enemy/wave1_and_wave_2/Dragon 4.png");
	imgDragonFire = iLoadImage("images/enemy/wave1_and_wave_2/fireballs.png");

	imgMedals[0] = iLoadImage("images/enemy/wave1_and_wave_2/Gold.png");
	imgMedals[1] = iLoadImage("images/enemy/wave1_and_wave_2/Silver.png");
	imgMedals[2] = iLoadImage("images/enemy/wave1_and_wave_2/Bronze.png");
}