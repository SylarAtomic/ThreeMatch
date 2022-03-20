#include "GemObject.h"
#include "TextureManager.h"
#include <iostream>

GemObject::GemObject()
{

}

GemObject::GemObject(const char* textureSheet, SDL_Renderer* _renderer, int x, int y)
{
	renderer = _renderer;
	gemTexture = TextureManager::LoadTexture(textureSheet, _renderer);

	xPos = x;
	yPos = y;
	updatePosX = x;
	updatePosY = y;

}

void GemObject::Update()
{
	//xPos = 0;
	//yPos = 100;

	//srcRect.h = 128;
	//srcRect.w = 128;
	//srcRect.x = 0;
	//srcRect.y = 0;

	if (updatePosX != xPos)
	{
		if (updatePosX > xPos) {
			xPos++;
		}
		else {
			xPos--;
		}
	}

	if (updatePosY != yPos)
	{
		if (updatePosY > yPos) {
			yPos++;
		}
		else {
			yPos--;
		}
	}

	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = gemSize;
	destRect.h = gemSize;

}

void GemObject::Render()
{

	SDL_RenderCopy(renderer, gemTexture, NULL, &destRect);
}

void GemObject::UpdatePostion(int newX, int newY)
{
	updatePosX = newX;
	updatePosY = newY;
}
