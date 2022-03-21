#include "GemObject.h"
#include "TextureManager.h"
#include <iostream>

/*
* Individual gem class
*/

GemObject::GemObject()
{

}

// Create a gem
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

// On update, we check to see if the update and pos are out of sync, if so, lets get moving the gem to its new position
// This is called every time 1/60 per second
void GemObject::Update()
{
	//  Animated the movement from the current position to where the gem needs to move to
	// X Update
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

	// Y Update
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

	// finally, make sure to acutally update the world position of the gem
	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = gemSize;
	destRect.h = gemSize;

}

// Displays the gem on screen
void GemObject::Render()
{

	SDL_RenderCopy(renderer, gemTexture, NULL, &destRect);
}

// Update only the x value (column)
void GemObject::UpdatePostion(int newX)
{
	updatePosX = newX;
}

// Update both x and y (column and row) - This is better way of doing it
void GemObject::UpdatePostion(int newX, int newY)
{
	updatePosX = newX;
	updatePosY = newY;
}

// Update the current texture, good for change a gems type!
void GemObject::UpdateGemTexture(const char* textureSheet)
{
	gemTexture = TextureManager::LoadTexture(textureSheet, renderer);
}

// Update the Y position: TODO make a specific x and y version of this. Instead of an overloaded function UpdatePostion
void GemObject::SetColumnPosition(int pos)
{
	yPos = pos;
}

