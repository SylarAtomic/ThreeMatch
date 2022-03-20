#include "GemObject.h"
#include "TextureManager.h"
#include <iostream>

GemObject::GemObject()
{

}

GemObject::GemObject(const char* textureSheet, SDL_Renderer* _renderer, int x, int y, int _type)
{

	renderer = _renderer;
	gemType = _type;
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

	//  Animated the movement from the current position to where the gem needs to move to
	if (updatePosX != xPos)
	{
		isUpdating = true;
		if (updatePosX > xPos) {
			xPos += gemMoveSpeed;
		}
		else {
			xPos -= gemMoveSpeed;
		}
	}
	else {

		isUpdating = false;
	}

	if (updatePosY != yPos)
	{
		isUpdating = true;
		if (updatePosY > yPos) {
			yPos += gemMoveSpeed;
		}
		else {
			yPos -= gemMoveSpeed;
		}
	}
	else {
		
		isUpdating = false;
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

void GemObject::UpdatePostion(int newX)
{
	updatePosX = newX;
}

void GemObject::UpdatePostion(int newX, int newY)
{
	updatePosX = newX;
	updatePosY = newY;
}

void GemObject::UpdateGemTexture(const char* textureSheet)
{
	gemTexture = TextureManager::LoadTexture(textureSheet, renderer);
}

void GemObject::SetColumnPosition(int pos)
{
	yPos = pos;
}

