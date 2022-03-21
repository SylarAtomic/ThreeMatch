#include "Game.h"
#include <iostream>

#include "TextureManager.h"
#include "GemObject.h"
#include "Grid.h"
#include "TextDrawer.h"

GemObject* gem;
GemObject* gemTwo;
GemObject* gemThree;
Grid* grid;
TTF_Font* FontAreal;

SDL_Event Game::event;

//GemObject* GemArrayTest[5] = { gem , gem , gem , gem , gem };

SDL_Texture* TextureBackground;
SDL_Texture* EndScreen;
SDL_Texture* TextureGem;
TextDrawer* ScoreText;

SDL_Rect srcR, destR;

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

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

	TextureBackground = TextureManager::LoadTexture("textures/Background.jpg", renderer);
	EndScreen = TextureManager::LoadTexture("textures/EndScreen.png", renderer);
	TextureGem = TextureManager::LoadTexture("textures/BlueGem.png", renderer);


	FontAreal = TTF_OpenFont("font/arial.ttf", 24);

	//gem = new GemObject("textures/BlueGem.png", renderer, 500, 500);
	//gemTwo = new GemObject("textures/GreenGem.png", renderer, 400, 500);
	//gemThree = new GemObject("textures/RedGem.png", renderer, 300, 500);

	ScoreText = new TextDrawer(renderer);

	ScoreText->SetToDefaultPosition();

	grid = new Grid(renderer);

	std::cout << renderer << std::endl;





	//GemArrayTest[0] = new GemObject("textures/GreenGem.png", renderer, 200, 500);
	//std::cout << GemArrayTest << std::endl; 
	//std::cout << GemArrayTest[0] << std::endl;
	//std::cout << GemArrayTest[1] << std::endl;

	//grid(renderer);
	// Build the Grid
	// 
	//grid.BuildStartingGrid();
}

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

void Game::hanldeMouseClick()
{
	int x, y;
	Uint32 buttons;

	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);

	SDL_Log("Mouse cursor is at %d, %d", x, y);

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
		// Check if the mouse click took place over a gem
		if (x < gridSize && y < gridSize)
		{
			std::cout << "Gem was clicked on!" << std::endl;

			int gemArrayPosX = floor(x / gemSize);
			int gemArrayPosY = floor(y / gemSize);

			handleGemRemove(gemArrayPosX, gemArrayPosY);
		}
	}
}

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

void Game::handleGemRemove(int xPos, int yPos)
{
	grid->RemoveGem(xPos, yPos);
	gameCount++;
}

void Game::update()
{
	grid->UpdateGrid();
}

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

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}