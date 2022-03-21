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
	TextureGem = TextureManager::LoadTexture("textures/BlueGem.png", renderer);


	FontAreal = TTF_OpenFont("font/arial.ttf", 24);

	//gem = new GemObject("textures/BlueGem.png", renderer, 500, 500);
	//gemTwo = new GemObject("textures/GreenGem.png", renderer, 400, 500);
	//gemThree = new GemObject("textures/RedGem.png", renderer, 300, 500);

	ScoreText = new TextDrawer(renderer);

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

	// Check if the mouse click took place over a gem
	if (x < gridSize && y < gridSize)
	{
		std::cout << "Gem was clicked on!" << std::endl;

		int gemArrayPosX = floor(x / gemSize);
		int gemArrayPosY = floor(y / gemSize);

		handleGemRemove(gemArrayPosX, gemArrayPosY);
	

	//// find which gem was clicked on
	//// gird size is know, the postion is equal to the x value / the gem size
	
	//std::cout << "gemArrayPosX: " << gemArrayPosX << " gemArrayPosY:" << gemArrayPosY << std::endl;

	//// this check if we are on the first or second click
	//if (firstClickGemPosX == -1) {
	//	firstClickGemPosX = gemArrayPosX;
	//	firstClickGemPosY = gemArrayPosY;
	//}
	//else {
	//	secondClickGemPosX = gemArrayPosX;
	//	secondClickGemPosY = gemArrayPosY;

	//	std::cout << "Swapping: [" << firstClickGemPosX << "," << firstClickGemPosY << "] and [" << secondClickGemPosX << "," << secondClickGemPosY << "]" << std::endl;

	//	handleGemSwap();
	//}

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
}

void Game::update()
{
	cnt++;
	destR.h = 128;
	destR.w = 128;

	destR.x = cnt;
	destR.y = 200;

	//gem->Update();
	//gemTwo->Update();
	grid->UpdateGrid();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	// Put all the items that will be rendered betwen RenderClear and RenderPresent!!!!!

	SDL_RenderCopy(renderer, TextureBackground, NULL, NULL);
	//SDL_RenderCopy(renderer, TextureGem, NULL, &destR);

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(FontAreal, "test", FontWhite);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	SDL_RenderCopy(renderer, Message, NULL, NULL);
	
	grid->RenderGrid();

	ScoreText->UpdateScore(grid->GetScore());
	ScoreText->RenderText();


	//GemArrayTest[0]->Render();


	// This is the final call, nothing should go below this
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}
