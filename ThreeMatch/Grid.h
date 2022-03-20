#pragma once
#include "GemObject.h"

class Grid {

public:
	Grid();
	Grid(SDL_Renderer* _renderer);
	void BuildStartingGrid();
	void RenderGrid();
	void UpdateGrid();

	GemObject* returnGemOne() { return gemOne; };

private:
	// functions
	int GetRandomNumber();
	int GetRandomNumberWithExclusion(int exclusion);
	void BuildImageGrid();
		// debugging
	void PrintGrid();

	// variables
	int startingGridArray[10][10];
	GemObject* gemArray[10][10];

	const int numberOfGems = 3;
	const int gemSize = 96;
	
	SDL_Renderer* renderer;

	GemObject* gemOne;
	GemObject* gemTwo;
	GemObject* gemThree;
	GemObject* gemFour;
	GemObject* gemFive;
};
