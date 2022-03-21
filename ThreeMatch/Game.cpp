#include "Game.h"
#include <iostream>
#include "TextureManager.h"
#include "GemObject.h"
#include "Grid.h"
#include "TextDrawer.h"

SDL_Event Game::event;

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	// if we should launch in fullscreen
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised successfully :-)" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created! Yay" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created! Nice" << std::endl;
		}
		
		running = true;
	}
	else {
		running = false;
	}
	 
	// Set the background image texture
	TextureBackground = TextureManager::LoadTexture("textures/Background.jpg", renderer);

	// Set the end screen image texture
	EndScreen = TextureManager::LoadTexture("textures/EndScreen.png", renderer);

	// Create the score screen (disapled on the top right)
	ScoreText = new TextDrawer(renderer);

	// Set score screen to default position
	ScoreText->SetToDefaultPosition();

	// Create the grid of gems
	grid = new Grid(renderer);
}

// Handle events like quit and button press
void Game::handleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		running = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		hanldeMouseClick();
		break;
	default:
		break;
	}
}

// Handles button click - Depending on game state, will  be used to clicking on gems or buttons
void Game::hanldeMouseClick()
{
	// x, y values for the mouse click location
	int x, y;
	Uint32 buttons;

	// Make sure we have the latest mouse state.
	SDL_PumpEvents();  

	// Get the mouse button
	buttons = SDL_GetMouseState(&x, &y);
	
	// Debugging
	// SDL_Log("Mouse cursor is at %d, %d", x, y);

	/*
	* hasGameEnded = true - one score screen - checking to click on buttons
	* hasGameEnded = false - normal game loop - clicking on gems 
	*/
	if (hasGameEnded) {
		// this is a hack to check if we are clicking on the "button"
		
		// restart button check
		if (x < 920 && x > 654 && y > 612 && y < 700 ) {
			std::cout << "restart button clicked!" << std::endl;
			restartGame();
		}

		// quit button check
		if (x < 1270 && x > 1000 && y > 612 && y < 700) {
			std::cout << "quit button clicked!" << std::endl;
			clean();
		}

	} else 
	{
		// Check if the mouse click took place over a gem (inside the gem box)
		if (x < gridSize && y < gridSize)
		{
			// Debuggin
			// std::cout << "Gem was clicked on!" << std::endl;

			// help to convert from x / y to array position: range[0-9]
			int gemArrayPosX = floor(x / gemSize);
			int gemArrayPosY = floor(y / gemSize);

			// time to remove some gems, check for match, drop gems, all the fancy fancy
			handleGemRemove(gemArrayPosX, gemArrayPosY);
		}
	}
}

// This allows for swapping for two gems position
void Game::handleGemSwap()
{
	// check if valid swap
	int xMoveAmount = abs(firstClickGemPosX - secondClickGemPosX);
	int yMoveAmount = abs(firstClickGemPosY - secondClickGemPosY);

	// only allow movement in x to x or y to y, no diagonals 
	if (xMoveAmount != yMoveAmount && (xMoveAmount == 1 || yMoveAmount == 1))
	{
		grid->SwapGems(firstClickGemPosX, firstClickGemPosY, secondClickGemPosX, secondClickGemPosY);	
	}

	// finally reset all the arrayPostions - regardless of if a swap was valid
	firstClickGemPosX = -1;
	firstClickGemPosY = -1;
	secondClickGemPosX = -1;
	secondClickGemPosY = -1;
}

// Tell the grid to remove a gem and increase game count
void Game::handleGemRemove(int xPos, int yPos)
{
	grid->RemoveGem(xPos, yPos);
	gameCount++;
}

// This is called every tick - put all update stuff in here
void Game::update()
{
	grid->UpdateGrid();
}

// This is called every tick - all rerenders go in here
void Game::render()
{
	SDL_RenderClear(renderer);
	// Put all the items that will be rendered betwen RenderClear and RenderPresent!!!!!

	// Oh look a background
	SDL_RenderCopy(renderer, TextureBackground, NULL, NULL);

	// game count check
	if (gameCount == 10)
	{
		hasGameEnded = true;

		ScoreText->SetToEndGamePosition();
	}

	if (hasGameEnded) {
		SDL_RenderCopy(renderer, EndScreen, NULL, NULL);
	}
	else {
		grid->RenderGrid();
	}
	
	// Update the score
	ScoreText->UpdateScore(grid->GetScore());

	// Update the Score renderer
	ScoreText->RenderText();

	// This is the final call, nothing should go below this, otherwise it wont render :-(
	SDL_RenderPresent(renderer);
}

// Reset value and restart the game
void Game::restartGame()
{
	// Reset game counter
	gameCount = 0;

	// Reset grid score
	grid->Restart();

	// Reset the score
	ScoreText->UpdateScore(0);

	// Reset the position of the score value
	ScoreText->SetToDefaultPosition();

	// Update the game state
	hasGameEnded = false;
}

// The finally count down I mean call. Put all the clean up in here. 
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}