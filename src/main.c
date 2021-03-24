/*******************************************************************************************
*
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "structs.h"
#include "DrawFunctions.h"
#include "InputChecks.h"
#include "Enemies.h"
#include "general.h"
#include <string.h>
#include "PixelFont.h"




const int WIDTH = 250, HEIGHT = 220;

Texture2D StoneTile;
Texture2D StoneWall;
Texture2D CharacterSpriteSheet;
Texture2D SwordSpriteSheet;


struct MapTextures DungeonTextures;


struct Enemy Enemies[16];


static Font LoadFont_PixelFont(void)
{
	Font font = { 0 };

	font.baseSize = 32;
	font.glyphCount = 95;
	font.glyphPadding = 4;

	// Custom font loading
	// NOTE: Compressed font image data (DEFLATE), it requires DecompressData() function
	int fontDataSize_PixelFont = 