#include "TextDrawer.h"
#include "TextureManager.h"
#include <string>
#include <iostream>

TextDrawer::TextDrawer()
{

}

TextDrawer::TextDrawer(SDL_Renderer* _renderer)
{
	renderer = _renderer;

	scoreTexture = TextureManager::LoadTexture("textures/Score.png", _renderer);


	scoreDestRect.w = 380;
	scoreDestRect.h = 128;

	BuildDigitTextureArray();

	digitOne = GetTexture(0);
	digitTwo = GetTexture(0);
	digitThree = GetTexture(0);
	digitFour = GetTexture(0);

	digitOneDestRect.w = 128;
	digitOneDestRect.h = 128;

	digitTwoDestRect.w = 128;
	digitTwoDestRect.h = 128;

	digitThreeDestRect.w = 128;
	digitThreeDestRect.h = 128;

	digitFourDestRect.w = 128;
	digitFourDestRect.h = 128;


	
}

void TextDrawer::UpdateScore(int value)
{
	score = value;

	UpdateDigitTextures();
	UpdateDigitDisplay();

}

void TextDrawer::RenderText()
{
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreDestRect);

	SDL_RenderCopy(renderer, digitOne, NULL, &digitOneDestRect);
	SDL_RenderCopy(renderer, digitTwo, NULL, &digitTwoDestRect);
	SDL_RenderCopy(renderer, digitThree, NULL, &digitThreeDestRect);
	SDL_RenderCopy(renderer, digitFour, NULL, &digitFourDestRect);

}

void TextDrawer::BuildDigitTextureArray()
{
	std::string texturePath = "textures/";
	std::string textureType = ".png";

	// TODO: Make this into an for loop over the array
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

SDL_Texture* TextDrawer::GetTexture(int num)
{
	return digitArray[num];
}

void TextDrawer::UpdateDigitDisplay()
{
	digitOne = GetTexture(scoreDigitArray[3]);
	digitTwo = GetTexture(scoreDigitArray[2]);
	digitThree = GetTexture(scoreDigitArray[1]);
	digitFour = GetTexture(scoreDigitArray[0]);
}

void TextDrawer::UpdateDigitTextures()
{
	scoreDigitArray[0] = floor(score % 10);
	scoreDigitArray[1] = floor((score % 100) / 10);
	scoreDigitArray[2] = floor((score % 1000) / 100);
	scoreDigitArray[3] = floor((score % 10000) / 1000);
}