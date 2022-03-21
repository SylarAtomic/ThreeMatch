#pragma once
#include "GemObject.h"

class Grid {

public:
	Grid();
	Grid(SDL_Renderer* _renderer);
	void BuildStartingGrid();
	void RenderGrid();
	void UpdateGrid();
	void SwapGems(int firstGemXpos, int firstGemYPos, int secondGemXPos, int secondGemYPos);
	void RemoveGem(int x, int y);
	void MoveGemsDown();

	GemObject* returnGemOne() { return gemOne; };

private:
	// functions
	int GetRandomNumber();
	int GetRandomNumberWithExclusion(int exclusion);
	void CheckUpAndDown(int x, int y, int gemType);
	void CheckLeftRight(int x, int y, int gemType);
	const char* GetTextureFromNumber(int randNumber);
	void BuildImageGrid();
		// debugging
	void PrintGrid();

	// variables
	int startingGridArray[10][10];
	GemObject* gemArray[10][10];

	const int numberOfGems = 3;
	const int gemSize = 96;
	int gemsToAdd[10];
	
	SDL_Renderer* renderer;

	const char* BlueGemPath = "textures/BlueGem.png";
	const char* GreenGemPath = "textures/GreenGem.png";
	const char* RedGemPath = "textures/RedGem.png";

	int numberOfMatches = 0;
	int score = 0;

	GemObject* gemOne;
	GemObject* gemTwo;
	GemObject* gemThree;
	GemObject* gemFour;
	GemObject* gemFive;
};
