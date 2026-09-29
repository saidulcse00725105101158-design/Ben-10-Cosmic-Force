# Ben-10-Cosmic-Force
BEN 10: COSMIC FORCE
A 2D Ben 10 game project built with Visual Studio 2013, C++, and the iGraphics/GLUT teaching library.
🎮 How to Open
Unzip the project folder anywhere.
Double-click `Ben10_CosmicForce.sln` to open it in Visual Studio 2013.
Make sure the platform selector in the top toolbar is set to Win32 (not x64).
Press F5 or Ctrl + F5 to build and run the game.
> The `.exe` is built directly inside the `Ben10_CosmicForce` folder, next to the `images/`, `Audios/`, and `font/` folders. This allows the game to find its assets when launched from Visual Studio or by double-clicking the `.exe`.
🔧 If the Build Fails
Platform Toolset Error
If you see:
```text
Platform Toolset v120 not found
```
Install the required Visual C++ 2013 tools, or:
Right-click the project.
Select Properties.
Go to General → Platform Toolset.
Select the Visual Studio 2013 toolset available on your machine.
Included Dependencies
Everything required by the project is included in the project folder:
`iGraphics.h`
`glut.h`
`.lib` files
`GLUT32.DLL`
Images
Audio
Fonts
You should not need to download additional libraries to run the provided project.
🎮 Controls
Key / Input	Action
A / D	Walk backward / forward
W	Jump
S	Crouch (hold)
SPACE	Attack
E	Cycle the Omnitrix to choose an alien
F	Transform into the selected alien
ESC	Pause the game and open the Main Menu
Mouse Click	Select menu buttons such as Start, High Scores, Exit, Resume, and Back
🕹️ Gameplay
The game starts on Level 1, configured by `STARTING_LEVEL` in `Config.h`.
Defeat 5 enemies to reach Level 2.
Level 2 contains tougher enemies that deal more damage.
Defeat 12 enemies in total to trigger the Boss fight.
Defeat the boss to win the game.
Your score is automatically saved if it reaches the Top 3.
High scores can be viewed from the Main Menu.
Transforming into Heatblast or Wildmutt lasts 10 seconds.
After transforming, there is a 5-second Omnitrix cooldown.
Levels 1 and 2 contain floating platforms.
Jump using W to land on platforms or clear them with a strong jump.
Walking underneath a floating platform at ground level allows you to pass underneath it.
There are no floating platforms during the boss fight.
Jumping or crouching at the right moment can dodge enemy attacks, boss attacks, and boss fireballs.
🖼️ Changing the Size of Images
Open:
```text
Config.h
```
At the beginning of the file, there is an IMAGE SIZES section containing the width and height of the game's images.
For example:
```cpp
// ---- Ben 10 (human form) ----
#define PLAYER_X            230
#define PLAYER_W             95   // width
#define PLAYER_H            170   // height (standing)
#define PLAYER_CROUCH_H     115   // height while crouching (S)
```
Change the required values and rebuild the project using F7.
The image will be resized everywhere it is used without needing to edit other files.
The configuration includes sizes for:
Backgrounds
Ground platform
Floating platforms
Ben 10
Heatblast
Wildmutt
Enemies
Boss
Omnitrix/watch icon
Health bar
Floating Platform Settings
The floating platforms have their own configuration:
```cpp
#define FLOATING_PLATFORM_W            220
#define FLOATING_PLATFORM_H             90
#define FLOATING_PLATFORM_Y_OFFSET     130   // height above the ground
#define FLOATING_PLATFORM_SPACING      650   // distance between platforms
```
> `JUMP_START_VELOCITY` in the gameplay section was raised from `15` to `20` so the floating platforms are comfortably reachable. Lower it if you make the platforms lower, or increase it if you place the platforms higher.
📁 Project Structure
```text
Ben10_CosmicForce.sln
│
├── Ben10_CosmicForce/
│   ├── Ben10_CosmicForce.vcxproj
│   ├── iMain.cpp
│   ├── Config.h
│   ├── Types.h
│   ├── Globals.h
│   ├── Assets.h
│   ├── HighScoreIO.h
│   ├── GameLogic.h
│   ├── UIHelpers.h
│   ├── Render.h
│   ├── InputAndUpdate.h
│   │
│   ├── iGraphics.h
│   ├── glut.h
│   ├── glaux.h
│   ├── stb_image.h
│   ├── bitmap_loader.h
│   │
│   ├── *.lib
│   ├── GLUT32.DLL
│   │
│   ├── images/
│   ├── Audios/
│   ├── font/
│   └── highscores.txt
```
Important Files
File	Description
`Ben10_CosmicForce.sln`	Opens the project in Visual Studio 2013
`Ben10_CosmicForce.vcxproj`	Visual Studio project file
`iMain.cpp`	Includes the modules and contains `main()`
`Config.h`	Game sizes, positions, damage, speed, timers, and other constants
`Types.h`	Enums and structures such as `Enemy`, `Boss`, `Fireball`, and `Rect`
`Globals.h`	Global game variables, loaded images, player, enemies, boss, scores, menus, and key flags
`Assets.h`	Loads game images
`HighScoreIO.h`	Loads, saves, and manages the Top 3 high scores
`GameLogic.h`	Game reset, enemy/boss spawning, attacks, damage, and dodge logic
`UIHelpers.h`	UI helper functions such as buttons and image rendering
`Render.h`	Rendering and drawing functions
`InputAndUpdate.h`	Mouse input, game updates, and related helpers
`images/`	Game images and visual assets
`Audios/`	Game audio
`font/`	Font files
`highscores.txt`	Created automatically to store the Top 3 scores
📌 Note About the Multiple `.h` Files
The iGraphics teaching library does not use include guards and defines its functions directly inside the header. Because of this, `iGraphics.h` can only be included from one `.cpp` file in the project.
To keep the project organized, the different modules are separated into headers, each using:
```cpp
#pragma once
```
`iMain.cpp` includes these modules in the required order.
This allows the game to remain separated into readable sections such as:
Rendering
Input
Game logic
Asset loading
UI
High-score management
Even though these are separate files, they are ultimately compiled through the single `iMain.cpp` translation unit.
📄 License
No license information is specified in the original project README.
⭐ Project
BEN 10: COSMIC FORCE
Built as a Visual Studio 2013 C++ game project using the iGraphics/GLUT teaching library.
