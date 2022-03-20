#include "Grid.h"
#include <stdlib.h>
#include <iostream>
#include <string>

Grid::Grid()
{

}


Grid::Grid(SDL_Renderer* _renderer)
{
	renderer = _renderer;

	// Build the starting array
	BuildStartingGrid();

	// Build the display array

	BuildImageGrid();
}

void Grid::BuildStartingGrid()
{
	// 0 - Blue Gem
	// 1 - Gren Gem
	// 2 - Red Gem
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			// for the first colum in each row we don't need to check the row above before adding (should probably check the one above if not the firs row. TODO)
			if (j == 0)
			{
				// [0][0] block and be anything the gods of the rand determine, other blocks and blame the first one for their problems
				if (i > 0) {
					startingGridArray[i][j] = GetRandomNumberWithExclusion(startingGridArray[i - 1][j]);
				}
				else {
					startingGridArray[i][j] = GetRandomNumber();
				}
			}
			else {
				// set the array value to a value that != to the previous cell
				startingGridArray[i][j] = GetRandomNumberWithExclusion(startingGridArray[i][j - 1]);
			}
		}
	}

	// Debug to console
	PrintGrid();

}

// get a random number that isn't the one included
// this will allow us to have a number that WON'T be returned
int Grid::GetRandomNumberWithExclusion(int exclusion)
{
	int randomNumber = GetRandomNumber();

	while (randomNumber == exclusion) {
		randomNumber = GetRandomNumber();
	}

	// std::cout << "Exlucsion: " << exclusion << " randNumber: " << randomNumber << std::endl;

	return randomNumber;
}

void Grid::PrintGrid()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if ( j == 9) {
				std::cout << startingGridArray[i][j] << std::endl;
			}
			else {
				std::cout << startingGridArray[i][j] << " ";
			}
		}
	}
}

int Grid::GetRandomNumber()
{
	return rand() % 3;
}

// using the starting array, we will now build what will be shown on the screen
void Grid::BuildImageGrid()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			char texturePath;


			// 0 - Blue Gem - "textures/BlueGem.png"
			// 1 - Green Gem - "textures/GreenGem.png"
			// 2 - Red Gem - "textures/RedGem.png"
			switch (startingGridArray[i][j])
			{
			case 0:
				//texturePath = "textures/BlueGem.png";
				gemArray[i][j] = new GemObject("textures/BlueGem.png", renderer, i * gemSize, j * gemSize);
				break;
			case 1:
				//texturePath = "textures/GreenGem.png";
				gemArray[i][j] = new GemObject("textures/GreenGem.png", renderer, i * gemSize, j * gemSize);
				break;
			case 2:
				//texturePath = "textures/RedGem.png";
				gemArray[i][j] = new GemObject("textures/RedGem.png", renderer, i * gemSize, j * gemSize);
				break;
			default:
				break;
			}
			//new GemObject("textures/BlueGem.png", renderer, i * gemSize, j * gemSize);

//			gemArray[i][j] = new GemObject("textures/BlueGem.png", renderer, i * gemSize, j * gemSize);
		}
	}


	//gemOne =  new GemObject("textures/BlueGem.png", renderer, 0 * gemSize, 0 * gemSize);
	//gemTwo = new GemObject("textures/GreenGem.png", renderer, 0 * gemSize, 1 * gemSize);
	//gemThree = new GemObject("textures/RedGem.png", renderer, 0 * gemSize, 2 * gemSize);
	//gemFour = new GemObject("textures/BlueGem.png", renderer, 400, 400);
	//gemFive = new GemObject("textures/GreenGem.png", renderer, 200, 200);

	//std::cout << renderer << std::endl;

	//std::cout << "Finished build image grid" << std::endl;
}

void Grid::RenderGrid()
{
	//gemOne->Render();
	//gemTwo->Render();
	//gemThree->Render();
	//gemFour->Render();
	//gemFive->Render();

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gemArray[i][j]->Render();
		}
	}

}

void Grid::UpdateGrid()
{

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gemArray[i][j]->Update();
		}
	}


	//gemOne->Update();
	//gemTwo->Update();
	//gemThree->Update();
	//gemFour->Update();
	//gemFive->Update();

}
