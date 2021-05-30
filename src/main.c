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
	int fontDataSize_PixelFont = 0;
	unsigned char* data = DecompressData(fontData_PixelFont, COMPRESSED_DATA_SIZE_FONT_PIXELFONT, &fontDataSize_PixelFont);
	Image imFont = { data, 512, 512, 1, 2 };

	// Load texture from image
	font.texture = LoadTextureFromImage(imFont);
	UnloadImage(imFont);  // Uncompressed data can be unloaded from memory

	// Assign glyph recs and info data directly
	// WARNING: This font data must not be unloaded
	font.recs = fontRecs_PixelFont;
	font.glyphs = fontGlyphs_PixelFont;

	return font;
}







int Game()
{
	int Tick = 0;
	int PlayerHealth = 25;
	int MaxHealth = 25;
	int PlayerAttack = 0;
	int CurrentPlayerAnimationFrame = 0;
	int AttackStartTick = 0;

	int PlayerAnimation[4] = {0, 2, 1, 2};
	int AttackAnimationWalking[2] = { 4, 3 };
	int AttackAnimationStanding[2] = { 5, 2 };

	bool moving = false;
	bool PlayerAttacking = false;
	bool AttackAnimation = false;


	StoneTile = LoadTexture("resources/StoneTile.png");
	StoneWall = LoadTexture("resources/StoneWall.png");
	CharacterSpriteSheet = LoadTexture("resources/CharacterSpriteSheet.png");
	SwordSpriteSheet = LoadTexture("resources/SwordSpriteSheet.png");

	Vector2 PreviousPlayerPosition = { 200, 200 };
	Vector2 PlayerPosition = { 200, 200 };
	Vector2 PlayerMovement = { 0, 0 };

	Font PixelFont = LoadFont_PixelFont();







	struct Sprite CharacterSprite;
	struct Sprite EnemySprite;
	

	struct Enemy Dummy;

	struct Item ItemHeld;

	DungeonTextures.Floors[0] = &StoneTile;
	DungeonTextures.Walls[0] = &StoneWall;



	CharacterSprite.SpriteSheet = &CharacterSpriteSheet;
	CharacterSprite.SpriteLength = 10;
	CharacterSprite.SpriteHeight = 15;
	CharacterSprite.CurrentSprite.x = 0;
	CharacterSprite.CurrentSprite.y = 0;


	EnemySprite.SpriteHeight = 15;
	EnemySprite.SpriteLength = 10;
	EnemySprite.CurrentSprite.y = 0;
	EnemySprite.CurrentSprite.x = 0;
	EnemySprite.SpriteSheet = &CharacterSpriteSheet;


	ItemHeld.IsOnTop[0] = true;
	ItemHeld.IsOnTop[3] = false;
	ItemHeld.IsOnTop[1] = false;
	ItemHeld.IsOnTop[2] = true;
	ItemHeld.OffSet[0].x = 0;
	ItemHeld.OffSet[1].x = 0;
	ItemHeld.OffSet[2].x = 0;
	ItemHeld.OffSet[3].x = 0;
	ItemHeld.OffSet[0].y = 0;
	ItemHeld.OffSet[1].y = 0;
	ItemHeld.OffSet[2].y = 0;
	ItemHeld.OffSet[3].y = 0;
	ItemH