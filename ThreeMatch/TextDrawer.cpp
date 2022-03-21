#include "TextDrawer.h"
#include "TextureManager.h"
#include <string>
#include <iostream>

/*
* "Draws" the score to screen
* Had an issue where the SDL_ttf help coming back as null. Can be fixed with more time but since I was limited,
* I went with something I knew I could do quickly
*/

TextDrawer::TextDrawer()
{

}

TextDrawer::TextDrawer(SDL_Renderer* _renderer)
{
	renderer = _renderer;

	// The "Score:" image
	scoreTexture = TextureManager::LoadTexture("textures/Score.png", _renderer);
	
	// Set width and height
	scoreDestRect.w = 380;
	scoreDestRect.h = 128;

	// Create the texture array
	BuildDigitTextureArray();

	// Set the digits to the "defualt" texture
	digitOne = GetTexture(0);
	digitTwo = GetTexture(0);
	digitThree = GetTexture(0);
	digitFour = GetTexture(0);

	// Set width and height
	digitOneDestRect.w = 128;
	digitOneDestRect.h = 128;

	// Set width and height
	digitTwoDestRect.w = 128;
	digitTwoDestRect.h = 128;

	// Set width and height
	digitThreeDestRect.w = 128;
	digitThreeDestRect.h = 128;

	// Set width and height
	digitFourDestRect.w = 128;
	digitFourDestRect.h = 128;
}

// Updates the score value - This then tells us we need to update the displayed digits
void TextDrawer::UpdateScore(int value)
{
	score = value;

	UpdateDigitTextures();
	UpdateDigitDisplay();

}

// Render function for all text related images
void TextDrawer::RenderText()
{
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreDestRect);

	SDL_RenderCopy(renderer, digitOne, NULL, &digitOneDestRect);
	SDL_RenderCopy(renderer, digitTwo, NULL, &digitTwoDestRect);
	SDL_RenderCopy(renderer, digitThree, NULL, &digitThreeDestRect);
	SDL_RenderCopy(renderer, digitFour, NULL, &digitFourDestRect);
}

// Creates a array of store textures where array index is the digit
void TextDrawer::BuildDigitTextureArray()
{
	std::string texturePath = "textures/";
	std::string textureType = ".png";

	// TODO: Make this into a for loop over the array, string hate me
	digitArray[0] = TextureManager::LoadTexture("textures/0.png", renderer);
	digitArray[1] = TextureManager::LoadTexture("textures/1.png", renderer);
	digitArray[2] = TextureManager::LoadTexture("textures/2.png", renderer);
	digitArray[3] = TextureManager::LoadTexture("textures/3.png", renderer);
	digitArray[4] = TextureManager::LoadTexture("textures/4.png", renderer);
	digitArray[5] = TextureManager::LoadTexture("textures/5.png", renderer);
	digitArray[6] = TextureManager::LoadTexture("textures/6.png", renderer);
	digitArray[7] = TextureManager::LoadTexture("textures/7.png", renderer);
	digitArray[8] = TextureManager::LoadTexture("textures/8.png", renderer);
	digitArray[9] = TextureManager::LoadTexture("textures/9.png", renderer);

	for (int i = 0; i < 4; i++)
	{
		scoreDigitArray[i] = 0;
	}
}

// Update the position of the score module components - Beter if this was all in a container and we moved the container
void TextDrawer::UpdateTextPosition()
{
	scoreDestRect.x = startingPosX - 320;
	scoreDestRect.y = startingPosY;

	digitOneDestRect.x = startingPosX;
	digitOneDestRect.y = startingPosY;

	digitTwoDestRect.x = startingPosX + (digitOffset);
	digitTwoDestRect.y = startingPosY;

	digitThreeDestRect.x = startingPosX + (digitOffset * 2);
	digitThreeDestRect.y = startingPosY;

	digitFourDestRect.x = startingPosX + (digitOffset * 3);
	digitFourDestRect.y = startingPosY;
}

// Get a texture base on a number we set, 0 is 0 texture, ect
SDL_Texture* TextDrawer::GetTexture(int num)
{
	return digitArray[num];
}

// Update digits with a display texture base on score
void TextDrawer::UpdateDigitDisplay()
{
	digitOne = GetTexture(scoreDigitArray[3]);
	digitTwo = GetTexture(scoreDigitArray[2]);
	digitThree = GetTexture(scoreDigitArray[1]);
	digitFour = GetTexture(scoreDigitArray[0]);
}

// Work out digit values
void TextDrawer::UpdateDigitTextures()
{
	scoreDigitArray[0] = floor(score % 10);
	scoreDigitArray[1] = floor((score % 100) / 10);
	scoreDigitArray[2] = floor((score % 1000) / 100);
	scoreDigitArray[3] = floor((score % 10000) / 1000);
}