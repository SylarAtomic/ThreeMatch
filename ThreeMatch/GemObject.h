#pragma once
#include "Game.h"

class GemObject {
public:
	GemObject();
	GemObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y);

	void Update();
	void Render();
	void ChangeTexture(const char* textureSheet);
	void UpdatePostion(int newX, int newY);

private:
	int xPos = 0;
	int yPos = 0;
	int updatePosX = 0;
	int updatePosY = 0;
	
	// 0 - Blue Gem
	// 1 - Gren Gem
	// 2 - Red Gem
	int gemType;
	int gemSize = 96;

	SDL_Texture* gemTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};