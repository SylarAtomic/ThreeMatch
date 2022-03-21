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
	void Restart();

	int GetScore() { return score; };

private:
	// Functions
	int GetRandomNumber();
	int GetRandomNumberWithExclusion(int exclusion);
	
	void CheckUpAndDown(int x, int y, int gemType);
	void CheckLeftRight(int x, int y, int gemType);
	void BuildImageGrid();

	const char* GetTextureFromNumber(int randNumber);
		// debugging
	void PrintGrid();

	// Variables
	// Holds a array of GemObjects
	GemObject* gemArray[10][10];

	const int numberOfGems = 3;
	const int gemSize = 96;
	const char* BlueGemPath = "textures/BlueGem.png";
	const char* GreenGemPath = "textures/GreenGem.png";
	const char* RedGemPath = "textures/RedGem.png";
	int startingGridArray[10][10];
	int gemsToAdd[10];
	int score = 0;
	int numberOfMatches = 0;

	SDL_Renderer* renderer;
};
