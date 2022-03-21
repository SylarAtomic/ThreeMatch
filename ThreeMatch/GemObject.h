#pragma once
#include "Game.h"

class GemObject {
public:
	GemObject();
	GemObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y, int type);

	void Update();
	void Render();
	void UpdatePostion(int newX);
	void UpdatePostion(int newX, int newY);
	void UpdateGemTexture(const char* textureSheet);
	void SetGemType(int value) { gemType = value; };
	void SetGemForDeletion(bool value) { isDeleted = value; };
	void SetColumnPosition(int pos);

	bool GemDeletionStatus() { return isDeleted; };

	int  GetGemType() { return gemType; };

private:
	int xPos = 0;
	int yPos = 0;
	int updatePosX = 0;
	int updatePosY = 0;
	int isUpdating = false;
	int isDeleted = false;
	
	// 0 - Blue Gem
	// 1 - Gren Gem
	// 2 - Red Gem
	int gemType = - 1;
	int gemSize = 96;

	// must be a factor of 96!
	int gemMoveSpeed = 2;

	SDL_Texture* gemTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};