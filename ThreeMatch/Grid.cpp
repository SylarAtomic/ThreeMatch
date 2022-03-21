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

void Grid::Restart()
{

	std::cout << "Game is restarting... Good luck!" << std::endl;

	// Build the starting array
	BuildStartingGrid();

	// Build the display array
	BuildImageGrid();

	// Reset the score, no cheating!!!
	score = 0;
}

void Grid::BuildStartingGrid()
{
	// 0 - Blue Gem
	// 1 - Gren Gem
	// 2 - Red Gem
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			// for the first column in each row we don't need to check the row above before adding (should probably check the one above if not the first row. TODO)
			if (j == 0)
			{
				// [0][0] block and be anything the gods of the rand determine, other blocks can blame the first one for their problems
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
				std::cout << "my name is: " << i << j << std::endl;
			}
		}
	}

	// this is used for adding gem in when we remove gems
	for (int i = 0; i < 10; i++) {
		gemsToAdd[i] = 0;
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
				gemArray[i][j] = new GemObject("textures/BlueGem.png", renderer, i * gemSize, j * gemSize, 0);
				break;
			case 1:
				//texturePath = "textures/GreenGem.png";
				gemArray[i][j] = new GemObject("textures/GreenGem.png", renderer, i * gemSize, j * gemSize, 1);
				break;
			case 2:
				//texturePath = "textures/RedGem.png";
				gemArray[i][j] = new GemObject("textures/RedGem.png", renderer, i * gemSize, j * gemSize, 2);
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

void Grid::SwapGems(int firstGemXpos, int firstGemYPos, int secondGemXPos, int secondGemYPos)
{
	// Update the postions of the gems (otherwise they will stay where they are)
	gemArray[firstGemXpos][firstGemYPos]->UpdatePostion(secondGemXPos * gemSize, secondGemYPos * gemSize);
	gemArray[secondGemXPos][secondGemYPos]->UpdatePostion(firstGemXpos * gemSize, firstGemYPos * gemSize);;
	// Debug - before swap
	std::cout << gemArray[firstGemXpos][firstGemYPos] << std::endl;
	std::cout << gemArray[secondGemXPos][secondGemYPos] << std::endl;

	// Swap the gems in the gem array
	std::swap(gemArray[firstGemXpos][firstGemYPos], gemArray[secondGemXPos][secondGemYPos]);
	std::cout << "Swapped!" << std::endl;

	// Debug - after swap
	std::cout << gemArray[firstGemXpos][firstGemYPos] << std::endl;
	std::cout << gemArray[secondGemXPos][secondGemYPos] << std::endl;
}

void Grid::RemoveGem(int x, int y)
{
	int gemType = gemArray[x][y]->GetGemType();
	gemArray[x][y]->UpdateGemTexture("textures/BlankGem.png");
	gemArray[x][y]->SetGemForDeletion(true);
	numberOfMatches++;

	/*gemArray[x][y - 1]->UpdateGemTexture("textures/BlankGem.png");
	gemArray[x][y - 1]->SetGemForDeletion(true);

	gemArray[x][y + 1]->UpdateGemTexture("textures/BlankGem.png");
	gemArray[x][y + 1]->SetGemForDeletion(true);

	gemArray[x + 1][y + 1]->UpdateGemTexture("textures/BlankGem.png");
	gemArray[x + 1][y + 1]->SetGemForDeletion(true);*/

	// we update this array so we know how many gems need to be spawned in
	gemsToAdd[x] = gemsToAdd[x]++;
	//gemsToAdd[x] = gemsToAdd[x]++;
	//gemsToAdd[x] = gemsToAdd[x]++;
	//gemsToAdd[x + 1] = gemsToAdd[x]++;

	std::cout << "gemsToAdd: " << gemsToAdd[x] << std::endl;

	CheckUpAndDown(x, y, gemType);
	CheckLeftRight(x, y, gemType);

	//int gemType = gemArray[x][y]->GetGemType();

	//for(int i = y + 1; i < 10; i++)
	//{
	//	if (gemArray[x][i]->GetGemType() == gemType) {
	//		// we have a match to the gem to our right
	//		// we need to remove this gem as well
	//		gemsToAdd[i]++;

	//		RemoveGem(x, i);
	//	}
	//	else {
	//		// no matching type on the right, lets exit early
	//		i = 10;
	//	}
	//}

	// lets figure out how many gems need to be removed

	// move the gem above the removed gem down, if a gem above, move do the same

	// once all gems have "fallen" spawn a new gem in


	// gemsToAdd[0] is equal to 3
	// this means in the first row we need to add THREE gems
	// loop through THAT Row
	
	MoveGemsDown();

	// finally update the score
	std::cout << "Number of matches: " << numberOfMatches << std::endl;

	score += numberOfMatches;

	std::cout << "Your current score is: " << score << std::endl;

	numberOfMatches = 0;
}

void Grid::MoveGemsDown()
{
	//for (int i = 0; i < 9; i++)
	//{
	//	for (int j = 0; j < 10; j++) {
	//		if (gemArray[i][j + 1]->GemDeletionStatus())
	//		{
	//			gemArray[i][j]->UpdatePostion(i * gemSize, (j + 1) * gemSize);
	//			gemArray[i][j - 1]->UpdatePostion(i * gemSize, j * gemSize);
	//			// Debug - before swap
	//			//std::cout << gemArray[firstGemXpos][firstGemYPos] << std::endl;
	//			//std::cout << gemArray[secondGemXPos][secondGemYPos] << std::endl;
	//		}
	//	}
	//}

	for (int i = 9; i > -1; i--) {
		for (int j = 9; j > -1; j--) {
			if (gemArray[i][j]->GemDeletionStatus())
			{
				// remove the block from deletion as we are reseting its value now
				gemArray[i][j]->SetGemForDeletion(false);

				// if true, this  means we can move a gem that is still on the board, yay!
				/*if (j - gemsToAdd[j] > 0) {
					int validItem = j - gemsToAdd[j];
				}*/

				// literally only the first row becaues I need a win :)
				if (j == 0 && gemsToAdd[i] == 1) {
					int randomNumber = GetRandomNumber();
					gemArray[i][j]->SetColumnPosition(-gemSize);
					gemArray[i][j]->UpdateGemTexture((GetTextureFromNumber(randomNumber)));
					gemArray[i][j]->SetGemType(randomNumber);

					std::cout << "Updating Gem!" << std::endl;

					gemsToAdd[i] = 0;
				}
				else {
					// for a single gem in a row anywhere on the board
					if (gemsToAdd[i] == 1) {
						GemObject* tempGem = gemArray[i][j];
						int numberOfSwaps = j;
						for (int m = 0; m < numberOfSwaps; m++) {
							//std::cout << "Swapping: [" << i << "," << j << "] with [" << numberOfSwaps << "," << j  << "]" << std::endl;
							std::cout << "Swapping: [" << i << "," << j << "] with [" << i << "," << numberOfSwaps - m - 1<< "]" << std::endl;
							gemArray[i][numberOfSwaps - m] = gemArray[i][numberOfSwaps - m - 1];
							gemArray[i][numberOfSwaps - m]->UpdatePostion(i * gemSize, (numberOfSwaps - m) * gemSize);
						}

						int randomNumber = GetRandomNumber();
						gemArray[i][0] = tempGem;
						gemArray[i][0]->SetColumnPosition(-gemSize);
						gemArray[i][0]->UpdatePostion(i * gemSize, 0);
						gemArray[i][0]->UpdateGemTexture((GetTextureFromNumber(randomNumber)));
						gemArray[i][0]->SetGemType(randomNumber);

						gemsToAdd[i] = 0;
					}
					else {
						int numberOfMoves = gemsToAdd[i];
						GemObject* tempArray[10];
						int arrayItemsCounter = 0;
						for (int m = 0; m < numberOfMoves; m++) {
							// this helps get the current deletions block
							int currentItem = j - m;
							gemArray[i][currentItem]->SetGemForDeletion(false);
							// this helps find which new index it will take
							//int newIndex = currentItem - numberOfMoves + 1;
							// we add one because arrays are zero indexed
							int newIndex = currentItem - (currentItem - numberOfMoves + 1 + m);
							std::cout << "item: [" << i << "," << currentItem << "] moved to array at [" << i << "," << newIndex << "]" << std::endl;

							// add the new block at the top
							int randomNumber = GetRandomNumber();
							gemArray[i][currentItem]->SetColumnPosition(-gemSize * (m + 1));
							//gemArray[i][currentItem]->UpdatePostion(gemSize * (numberOfMoves - 1 - m ), gemSize * i);
							gemArray[i][currentItem]->UpdatePostion(gemSize * i, gemSize * (numberOfMoves - 1 - m));
							gemArray[i][currentItem]->UpdateGemTexture((GetTextureFromNumber(randomNumber)));
							gemArray[i][currentItem]->SetGemType(randomNumber);

							tempArray[newIndex] = gemArray[i][currentItem];
							arrayItemsCounter++;
						}

						// we add one because arrays are zero indexed
						int itemsRemaining = j - numberOfMoves + 1;
						std::cout << itemsRemaining << std::endl;

						for (int m = 0; m < itemsRemaining; m++)
						{
							gemArray[i][m]->UpdatePostion(gemSize * i, gemSize * (m + numberOfMoves));
							tempArray[m + numberOfMoves] = gemArray[i][m];
							std::cout << "Moving item from " << m << " to " << m + numberOfMoves << std::endl;
							arrayItemsCounter++;
						}


						// add all the gems back to the orgianal array :-)
						for (int m = 0; m < arrayItemsCounter; m++) {
							gemArray[i][m] = tempArray[m];
						}

						// finished updating the row!
						gemsToAdd[i] = 0;
					}
				}
			}
		}
	}
}

// Given an random number, returns a gem asset path
const char* Grid::GetTextureFromNumber(int randNumber)
{
	switch (randNumber)
	{
	case 0:
		return BlueGemPath;
		break;
	case 1:
		return GreenGemPath;
		break;
	case 2:
		return RedGemPath;
		break;
	default:
		return BlueGemPath;
		break;
	}
}

void Grid::CheckUpAndDown(int x, int y, int gemType)
{
	
	if (y < 9)
	{
		// lets check up the column
		for (int i = y + 1; i <= 9; i++) {
			if (gemArray[x][i]->GetGemType() == gemType)
			{
				gemArray[x][i]->UpdateGemTexture("textures/BlankGem.png");
				gemArray[x][i]->SetGemForDeletion(true);
				numberOfMatches++;
				gemsToAdd[x] = gemsToAdd[x]++;
			}
			else {
				// exit as there is no point going on 
				break;
			}
		}
	}

	// lets check down the column
	if (y > 0) {
		for (int i = y - 1; i >= 0; i--) {
			if (gemArray[x][i]->GetGemType() == gemType)
			{
				gemArray[x][i]->UpdateGemTexture("textures/BlankGem.png");
				gemArray[x][i]->SetGemForDeletion(true);
				numberOfMatches++;
				gemsToAdd[x] = gemsToAdd[x]++;
			}
			else {
				// exit as there is no point going on 
				break;
			}
		}
	}
}

void Grid::CheckLeftRight(int x, int y, int gemType) {
	// lets check to the right
	if (x < 9)
	{
		for (int i = x + 1; i <= 9; i++) {
			if (gemArray[i][y]->GetGemType() == gemType)
			{
				gemArray[i][y]->UpdateGemTexture("textures/BlankGem.png");
				gemArray[i][y]->SetGemForDeletion(true);
				numberOfMatches++;
				gemsToAdd[i] = gemsToAdd[i]++;

				CheckUpAndDown(i, y, gemType);
			}
			else {
				// exit as there is no point going on 
				break;
			}
		}
	}

	// lets check to the left
	if (x > 0) {
		for (int i = x - 1; i >= 0; i--) {
			if (gemArray[i][y]->GetGemType() == gemType)
			{
				gemArray[i][y]->UpdateGemTexture("textures/BlankGem.png");
				gemArray[i][y]->SetGemForDeletion(true);
				numberOfMatches++;
				gemsToAdd[i] = gemsToAdd[i]++;

				CheckUpAndDown(i, y, gemType);
			}
			else {
				// exit as there is no point going on 
				break;
			}
		}
	}

}