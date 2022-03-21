#include "Grid.h"
#include <stdlib.h>
#include <iostream>
#include <string>

/*
* Builds a gird of GemObjects
*/

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

	CreateMinMatchs();
}

// Resets the gird and gets it ready to start again - Here we go again!
void Grid::Restart()
{
	// Debug
	std::cout << "Game is restarting... Good luck!" << std::endl;

	// Build the starting array
	BuildStartingGrid();

	// Build the display array
	BuildImageGrid();

	// After building the array, we need to add in at some possible matches
	CreateMinMatchs();

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
					// we can have the rows generate by checking item above it
					//startingGridArray[i][j] = GetRandomNumberWithExclusion(startingGridArray[i - 1][j]);
					startingGridArray[i][j] = GetRandomNumber();
				}
				else {
					startingGridArray[i][j] = GetRandomNumber();
				}
			}
			else {
				// set the array value to a value that != to the previous cell
				// startingGridArray[i][j] = GetRandomNumberWithExclusion(startingGridArray[i][j - 1]);
				startingGridArray[i][j] = GetRandomNumber();
			}
		}
	}

	// This is used for adding gem in when we remove gems
	// It keep track of how many gems were removed and helps with the moving logic
	for (int i = 0; i < 10; i++) {
		gemsToAdd[i] = 0;
	}

	// Debug to console
	// PrintGrid();
}

// TODO: This can be improved! Would be a good idea to pick a random direction as the start
// Need to move each of the "checks" to their own functions
// Updates the grid matches to make sure we have certain amount of matches
void Grid::CreateMinMatchs()
{
	// TODO move to own function
	bool checkArray[10][10];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			checkArray[i][j] = true;
		}
	}

	for (int i = 0; i < minMatches; i++) 
	{
		int randomXPos = rand() % 10;
		int randomYPos = rand() % 10;
		int counter = 0;
		bool isChecking = true;
		int randomGem = GetRandomNumber();

		while (isChecking) 
		{
			// Prevent it running until the end of time if the rand god aren't with us
			if (counter > 5)
			{
				std::cout << "Was not able to gaurentee " << minMatches << ". I have brought dishonor! :-(" << std::endl;
				isChecking = false;
			}

			// Start start by checking if we can fit in an a row
			// RIGHT
			if (randomXPos + minMatchSize <= 9) {
				// We can fit it allong the x axis
				// Now we check if we have put any gems in these locations before
				bool isSafe = true;

				for (int j = 0; j < minMatchSize; j ++)
				{
					// check if we can fit the block
					if (checkArray[randomXPos + j][randomYPos] == false) 
					{
						isSafe = false;
						break;
					}
				}

				if (isSafe)
				{
					for (int j = 0; j < minMatchSize; j++)
					{
						gemArray[randomXPos + j][randomYPos]->SetGemType(randomGem);
						gemArray[randomXPos + j][randomYPos]->UpdateGemTexture(GetTextureFromNumber(randomGem));
						checkArray[randomXPos + j][randomYPos] = false;
					}

					// Break the loop!
					isChecking = false;

					std::cout << "Place a " << minMatchSize << " at [" << randomXPos << "," << randomYPos << "] RIGHT Type: " << randomGem << std::endl;
				}
				
			}
			// to the left to the left!
			// LEFT
			else if (randomXPos - minMatchSize >= 0)
			{
				bool isSafe = true;

				for (int j = 0; j < minMatchSize; j++)
				{
					// check if we can fit the block
					if (checkArray[randomXPos - j][randomYPos] == false)
					{
						isSafe = false;
						break;
					}
				}

				if (isSafe)
				{
					for (int j = 0; j < minMatchSize; j++)
					{
						gemArray[randomXPos - j][randomYPos]->SetGemType(randomGem);
						gemArray[randomXPos - j][randomYPos]->UpdateGemTexture(GetTextureFromNumber(randomGem));
						checkArray[randomXPos - j][randomYPos] = false;
					}

					// Break the loop!
					isChecking = false;

					std::cout << "Place a " << minMatchSize << " at [" << randomXPos << "," << randomYPos << "] LEFT Type: " << randomGem << std::endl;
				}
			} 
			// well x is a pain so lets try side ways
			// DOWN
			else if (randomYPos + minMatchSize <= 9)
			{
				bool isSafe = true;

				for (int j = 0; j < minMatchSize; j++)
				{
					// check if we can fit the block
					if (checkArray[randomXPos][randomYPos + j] == false)
					{
						isSafe = false;
						break;
					}
				}

				if (isSafe)
				{
					for (int j = 0; j < minMatchSize; j++)
					{
						gemArray[randomXPos][randomYPos + j]->SetGemType(randomGem);
						gemArray[randomXPos][randomYPos + j]->UpdateGemTexture(GetTextureFromNumber(randomGem));
						checkArray[randomXPos][randomYPos + j] = false;
					}

					// Break the loop!
					isChecking = false;

					std::cout << "Place a " << minMatchSize << " at [" << randomXPos << "," << randomYPos << "] DOWN Type: " << randomGem  << std::endl;
				}
			}
			// UP
			//  
			else if (randomYPos - minMatchSize >= 0)
			{
				bool isSafe = true;

				for (int j = 0; j < minMatchSize; j++)
				{
					// check if we can fit the block
					if (checkArray[randomXPos][randomYPos - j] == false)
					{
						isSafe = false;
						break;
					}
				}

				if (isSafe)
				{
					for (int j = 0; j < minMatchSize; j++)
					{
						gemArray[randomXPos][randomYPos - j]->SetGemType(randomGem);
						gemArray[randomXPos][randomYPos - j]->UpdateGemTexture(GetTextureFromNumber(randomGem));
						checkArray[randomXPos][randomYPos - j] = false;
					}

					// Break the loop!
					isChecking = false;

					std::cout << "Place a " << minMatchSize << " at [" << randomXPos << "," << randomYPos << "] UP Type: " << randomGem  << std::endl;
				}
			}

			// reset the numbers as we couldn't find a valid match
			randomXPos = rand() % 10;
			randomYPos = rand() % 10;

			// increase the counter so we can try again
			counter++;
		}

	}

}

// Get a random number that isn't the one included
// This will allow us to have a number that WON'T be returned
int Grid::GetRandomNumberWithExclusion(int exclusion)
{
	int randomNumber = GetRandomNumber();

	while (randomNumber == exclusion) {
		randomNumber = GetRandomNumber();
	}

	// std::cout << "Exlucsion: " << exclusion << " randNumber: " << randomNumber << std::endl;

	return randomNumber;
}

// Debugging - Prints the grid to console
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

// Get a random number between 0 - 2
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
			// TODO: Use texturePath in the switch

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
		}
	}

	// Debugging
	//std::cout << "Finished build image grid" << std::endl;
}

// Calls render on all the gemObjects
void Grid::RenderGrid()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gemArray[i][j]->Render();
		}
	}

}

// Calls update on all the gemObjects
void Grid::UpdateGrid()
{

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gemArray[i][j]->Update();
		}
	}
}

// Created this to help swap two gems positions
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

// Removes a gem at x, y - Call for checking types near by
void Grid::RemoveGem(int x, int y)
{
	// GemType - Used for checking against other gems
	int gemType = gemArray[x][y]->GetGemType();

	// Set the gem to blank as we will be removing it
	gemArray[x][y]->UpdateGemTexture("textures/BlankGem.png");

	// Mark for deletions
	gemArray[x][y]->SetGemForDeletion(true);

	// Increase matches by 1
	numberOfMatches++;

	// Debugging - Sets up row or column removal of 3x1 or 1x3
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

	// Debug
	// std::cout << "gemsToAdd: " << gemsToAdd[x] << std::endl;

	// Initial call to update the row and column
	// TODO: This can be improve. It need to check at the end, UP, DOWN, RIGHT, LEFT. Should be recursive.
	CheckUpAndDown(x, y, gemType);
	CheckLeftRight(x, y, gemType);

	// After all the deletion, time to move all the gems down
	MoveGemsDown();

	// finally update the score
	std::cout << "Number of matches: " << numberOfMatches << std::endl;

	// Add matches to total score
	score += numberOfMatches;

	std::cout << "Your current score is: " << score << std::endl;

	// Reset the match back to 0
	numberOfMatches = 0;
}

// This handle moving the gems down when there is an open space
// TODO: this could definetly be simplied and improved but it was a good way of showing a little how I think
// Instead of solving the entire problems, I started by solving one part, then another and another.
// There is a bug :-( if  gems are removed around a "C" shape, it will not know what to do an leave a "ghost" gem
void Grid::MoveGemsDown()
{
	// This works backwards through the array
	for (int i = 9; i > -1; i--) {
		for (int j = 9; j > -1; j--) {
			// We first check if the gem we are removing has been marked for deletion, otherwise, why would we want to remove it
			if (gemArray[i][j]->GemDeletionStatus())
			{
				// remove the block from deletion as we are reseting its value now
				gemArray[i][j]->SetGemForDeletion(false);

				// literally only the first row becaues I need a win :)
				if (j == 0 && gemsToAdd[i] == 1) {
					int randomNumber = GetRandomNumber();
					gemArray[i][j]->SetColumnPosition(-gemSize);
					gemArray[i][j]->UpdateGemTexture((GetTextureFromNumber(randomNumber)));
					gemArray[i][j]->SetGemType(randomNumber);

					// Debug
					// std::cout << "Updating Gem!" << std::endl;

					gemsToAdd[i] = 0;
				}
				else {
					// for a single gem in a row anywhere on the board
					if (gemsToAdd[i] == 1) {
						GemObject* tempGem = gemArray[i][j];
						int numberOfSwaps = j;
						for (int m = 0; m < numberOfSwaps; m++) {
							//std::cout << "Swapping: [" << i << "," << j << "] with [" << i << "," << numberOfSwaps - m - 1<< "]" << std::endl;
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
						// All other cases
						int numberOfMoves = gemsToAdd[i];
						GemObject* tempArray[10];
						int arrayItemsCounter = 0;

						for (int m = 0; m < numberOfMoves; m++) {
							// This helps get the current deletion gem
							int currentItem = j - m;

							// Reset the gem state, we don't want to go over a gem after we have done all the fancy to it
							gemArray[i][currentItem]->SetGemForDeletion(false);

							// This helps find which new index it will take
							// We add one because arrays are zero indexed
							int newIndex = currentItem - (currentItem - numberOfMoves + 1 + m);

							// Debug - Very useful for find out what was being moved around
							// std::cout << "item: [" << i << "," << currentItem << "] moved to array at [" << i << "," << newIndex << "]" << std::endl;

							// Add the new gem at the top
							int randomNumber = GetRandomNumber();
							
							// Move the gem off screen
							gemArray[i][currentItem]->SetColumnPosition(-gemSize * (m + 1));

							// Tell the gem where it needs to move to
							gemArray[i][currentItem]->UpdatePostion(gemSize * i, gemSize * (numberOfMoves - 1 - m));

							// Update the texture to match random number
							gemArray[i][currentItem]->UpdateGemTexture((GetTextureFromNumber(randomNumber)));

							// Update type of the entire universe will go out of sync and we will need to call Dr Strange
							gemArray[i][currentItem]->SetGemType(randomNumber);

							// Add the gem to our "holding array"
							tempArray[newIndex] = gemArray[i][currentItem];
							
							// Increase the counter as I don't want to check how many elements aren't NULL
							arrayItemsCounter++;
						}

						// We add one because arrays are zero indexed
						int itemsRemaining = j - numberOfMoves + 1;

						// Debug
						// std::cout << itemsRemaining << std::endl;

						// Loop through the gems that haven't been "removed" these are the one that will need to move to where the deleted gems are
						for (int m = 0; m < itemsRemaining; m++)
						{
							// Update its position
							gemArray[i][m]->UpdatePostion(gemSize * i, gemSize * (m + numberOfMoves));

							// Add it to our temp array in its correct order
							tempArray[m + numberOfMoves] = gemArray[i][m];

							// Debug
							// std::cout << "Moving item from " << m << " to " << m + numberOfMoves << std::endl;

							// Increase the counter as I don't want to check how many elements aren't NULL
							arrayItemsCounter++;
						}

						// Add all the gems back to the orgianal array :-)
						for (int m = 0; m < arrayItemsCounter; m++) {
							gemArray[i][m] = tempArray[m];
						}

						// Finished updating the row!
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

// Checks for match Up the column, then down the column
void Grid::CheckUpAndDown(int x, int y, int gemType)
{
	
	if (y < 9)
	{
		// lets check up the column
		for (int i = y + 1; i <= 9; i++) {
			if (gemArray[x][i]->GetGemType() == gemType)
			{
				// Set the gem to the blank texture
				gemArray[x][i]->UpdateGemTexture("textures/BlankGem.png");

				// Mark it for deletion
				gemArray[x][i]->SetGemForDeletion(true);

				// Update the number of matches (this helps us keep score)
				numberOfMatches++;

				// Keep track of number of gems per column that need to be removed
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
				// Set the gem to the blank texture
				gemArray[x][i]->UpdateGemTexture("textures/BlankGem.png");

				// Mark it for deletion
				gemArray[x][i]->SetGemForDeletion(true);

				// Update the number of matches (this helps us keep score)
				numberOfMatches++;

				// Keep track of number of gems per column that need to be removed
				gemsToAdd[x] = gemsToAdd[x]++;
			}
			else {
				// exit as there is no point going on 
				break;
			}
		}
	}
}

// Check for match Left, then Right side of the row
void Grid::CheckLeftRight(int x, int y, int gemType) {

	// lets check to the right
	if (x < 9)
	{
		for (int i = x + 1; i <= 9; i++) {
			if (gemArray[i][y]->GetGemType() == gemType)
			{
				// Set the gem to the blank texture
				gemArray[i][y]->UpdateGemTexture("textures/BlankGem.png");

				// Mark it for deletion
				gemArray[i][y]->SetGemForDeletion(true);

				// Update the number of matches (this helps us keep score)
				numberOfMatches++;

				// Keep track of number of gems per column that need to be removed
				gemsToAdd[i] = gemsToAdd[i]++;

				// Call for checking down the same column
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
				// Set the gem to the blank texture
				gemArray[i][y]->UpdateGemTexture("textures/BlankGem.png");

				// Mark it for deletion
				gemArray[i][y]->SetGemForDeletion(true);

				// Update the number of matches (this helps us keep score)
				numberOfMatches++;

				// Keep track of number of gems per column that need to be removed
				gemsToAdd[i] = gemsToAdd[i]++;

				// Call for checking down the same column
				CheckUpAndDown(i, y, gemType);
			}
			else {
				// exit as there is no point going on 
				break;
			}
		}
	}

}