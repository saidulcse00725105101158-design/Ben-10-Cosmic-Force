// =====================================================================================
//  BEN 10 : COSMIC FORCE
//  CSE-1200 Software Development - I  |  AUST
//
//  Built on top of the iGraphics library (GLUT/OpenGL wrapper) used in class.
//
//  CONTROLS
//  --------
//     A / D        -> walk backward / forward   (scrolls the ground)
//     W            -> jump (also lands you on floating platforms in levels 1 & 2)
//     S            -> crouch (hold)
//     SPACE        -> attack
//     E            -> cycle the watch (choose an alien)
//     F            -> confirm transformation into the alien shown on the watch
//     ESC          -> pause game and open the Main Menu (Resume appears there)
//     Mouse click  -> used on every menu / button screen
//
//  Jumping and crouching both dodge enemy/boss attacks and the boss fireball.
//
//  HOW THE PROJECT IS ORGANISED
//  ------------------------------
//  The underlying iGraphics.h teaching library has no include guards and puts full
//  function bodies directly in the header, so it is only ever meant to be #include'd
//  from ONE .cpp file. To keep that working while still splitting the game into
//  readable files, every game module below is its own header (with #pragma once) that
//  is #include'd, in dependency order, from this single .cpp file. Nothing here is
//  compiled more than once, so there is no linker conflict - it reads and edits just
//  like separate files, because it is separate files.
//
//     Config.h          - EVERY size/position/gameplay constant (start here to resize
//                          or reposition an image, or tweak damage/speed/timers)
//     Types.h           - enums (GameState, AlienForm) and small structs (Enemy, Boss,
//                          Fireball, Rect)
//     Globals.h         - all global variables (loaded image IDs, player, enemies,
//                          boss, fireballs, high scores, menu buttons, key-edge flags)
//     Assets.h          - loadAllImages()
//     HighScoreIO.h     - load / save / insert the Top-3 high scores
//     GameLogic.h       - resetGame, spawnEnemy/spawnBoss, attack & damage rules,
//                          playerIsDodging()
//     UIHelpers.h       - pointInRect, drawButton, iShowImageFlip
//     Render.h          - every draw*() function + iDraw() (called every frame), and
//                          getFloatingPlatformUnderPlayer() (shared with input/physics)
//     InputAndUpdate.h  - iMouse() + fixedUpdate() and its helpers (called ~60/sec)
//
//  main() (right below) just opens the audio channels, creates the window, loads the
//  images and high scores, and hands control over to iStart().
// =====================================================================================

#define _CRT_SECURE_NO_WARNINGS
#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma comment(lib, "winmm.lib")   // needed for mciSendString (audio)

#include "CustomFont.h"       // 0) custom TrueType font rendering (iTextTTF)
#include "Config.h"           // 1) constants
#include "Types.h"            // 2) enums / structs
#include "Globals.h"          // 3) global variables
#include "Assets.h"           // 4) loadAllImages()
#include "HighScoreIO.h"      // 5) high-score file I/O
#include "GameLogic.h"        // 6) game rules (reset/spawn/attack/damage/dodge)
#include "UIHelpers.h"        // 7) small drawing helpers
#include "Render.h"           // 8) all draw*() functions + iDraw() + platform support check
#include "InputAndUpdate.h"   // 9) iMouse() + fixedUpdate()

// =====================================================================================
// main()
// =====================================================================================
int main()
{
    srand((unsigned int)time(NULL));

    // ---- audio ----
    mciSendString("open \"Audios//Main menu.mp3\" alias menusong", NULL, 0, NULL);
    mciSendString("open \"Audios//background.mp3\" alias gamesong", NULL, 0, NULL);
    mciSendString("open \"Audios//gameover.mp3\" alias gameoversong", NULL, 0, NULL);
    mciSendString("open \"Audios//hit.mp3\" alias hit", NULL, 0, NULL);
    mciSendString("open \"Audios//ben_10_watch.mp3\" alias watchsong", NULL, 0, NULL);
    mciSendString("open \"Audios//omnitrix_transform.mp3\" alias transformsong", NULL, 0, NULL);
    mciSendString("open \"Audios//gameover.mp3\" alias winsong", NULL, 0, NULL); // reuse gameover clip as a win jingle

    mciSendString("play menusong repeat", NULL, 0, NULL);

    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Ben 10: Cosmic Force", TICK_MS);
    iLoadCustomFont();   // needs the window/GL context iInitialize() just created

    loadHighScores();
    loadAllImages();
    resetGame();

    iStart();
    return 0;
}
