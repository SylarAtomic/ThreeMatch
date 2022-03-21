#pragma once
#include "Game.h"

class TextDrawer {
public:
	TextDrawer();
	~TextDrawer();
	TextDrawer(SDL_Renderer* _renderer);
	void UpdateScore(int value);
	void RenderText();
	void UpdateDigitDisplay();
	void UpdateDigitTextures();
	void BuildDigitTextureArray();
	void SetToDefaultPosition() { startingPosX = 1400; startingPosY = 0; UpdateTextPosition(); };
	void SetToEndGamePosition() { startingPosX = 980; startingPosY = 460; UpdateTextPosition(); };
	void UpdateTextPosition();
	SDL_Texture* GetTexture(int num);

private:
	int score = 0;
	int digitOffset = 50;
	int scoreDigitArray[4];

	int startingPosX = 1400;
	int startingPosY = 0;

	SDL_Renderer* renderer;
	SDL_Texture* scoreTexture;
	SDL_Rect scoreSrcRect, scoreDestRect;

	//Digits from left to right
	SDL_Texture* digitOne;
	SDL_Texture* digitTwo;
	SDL_Texture* digitThree;
	SDL_Texture* digitFour;

	SDL_Rect digitOneDestRect, digitTwoDestRect, digitThreeDestRect, digitFourDestRect;

	SDL_Texture* digitArray[10];
};
