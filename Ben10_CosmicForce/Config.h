#pragma once

#define SCREEN_WIDTH        1280
#define SCREEN_HEIGHT       600

#define MENUBG_W            SCREEN_WIDTH
#define MENUBG_H            SCREEN_HEIGHT
#define LEVELBG_W           SCREEN_WIDTH
#define LEVELBG_H           SCREEN_HEIGHT

#define PLATFORM_TILE_W     900
#define PLATFORM_TILE_H     450
#define PLATFORM_Y          0

#define FLOATING_PLATFORM_W 220
#define FLOATING_PLATFORM_H 90
#define FLOATING_PLATFORM_Y_OFFSET 130
#define FLOATING_PLATFORM_SPACING  650

#define GROUND_Y            140

#define PLAYER_X            230
#define PLAYER_W            75
#define PLAYER_H            120
#define PLAYER_CROUCH_H     105

#define HEATBLAST_W         105
#define HEATBLAST_H         195
#define FIREBALL_W          55
#define FIREBALL_H          33

#define WILDMUTT_W          130
#define WILDMUTT_H          130

#define ENEMY_W             160
#define ENEMY_H             200

#define BOSS_W              240
#define BOSS_H              280
#define BOSSFIRE_W          95
#define BOSSFIRE_H          88

#define DRAGON_W            160
#define DRAGON_H            160
#define DRAGON_FIRE_W       60
#define DRAGON_FIRE_H       40
#define MEDAL_W             40
#define MEDAL_H             40

#define WATCH_W             85
#define WATCH_H             95
#define WATCH_X             20
#define WATCH_Y             20

#define HEALTHBAR_W         260
#define HEALTHBAR_H         112
#define HEALTHBAR_X         15
#define HEALTHBAR_Y         (SCREEN_HEIGHT - HEALTHBAR_H - 12)

#define TICK_MS             16
#define WALK_SCROLL_SPEED   6
#define GRAVITY             1
#define JUMP_START_VELOCITY 20
#define ATTACK_RANGE        140
#define ATTACK_ANIM_MS      250
#define ATTACK_COOLDOWN_MS  380
#define TRANSFORM_DURATION_MS 10000
#define TRANSFORM_COOLDOWN_MS 5000

#define ENEMY_SPEED_L1      3
#define ENEMY_SPEED_L2      4
#define ENEMY_DAMAGE_L1     5
#define ENEMY_DAMAGE_L2     14
#define ENEMY_ATTACK_RANGE  25
#define ENEMY_ATTACK_COOLDOWN_MS 1000
#define ENEMY_MAX_HEALTH    30
#define ENEMY_SPAWN_MIN_MS  1400
#define ENEMY_SPAWN_MAX_MS  2400

#define BOSS_MAX_HEALTH     220
#define BOSS_SPEED          2
#define BOSS_DAMAGE         22
#define BOSS_ATTACK_RANGE   90
#define BOSS_ATTACK_COOLDOWN_MS 1400
#define BOSS_FIRE_COOLDOWN_MS   2600
#define BOSS_FIRE_SPEED     9
#define BOSS_FIRE_DAMAGE    15

#define DRAGON_ATTACK_RANGE 700
#define DRAGON_ATTACK_COOLDOWN_MS 700
#define DRAGON_FIRE_SPEED   10.0
#define DRAGON_FIRE_DAMAGE  8

#define PLAYER_ATTACK_DAMAGE_BEN10     12
#define PLAYER_ATTACK_DAMAGE_HEATBLAST 20
#define PLAYER_ATTACK_DAMAGE_WILDMUTT  35

#define STARTING_LEVEL      1
#define ENEMIES_TO_LEVEL2   5
#define ENEMIES_TO_BOSS     12
#define MAX_ENEMIES         6
#define MAX_DRAGONS         3  
#define MAX_MEDALS          5