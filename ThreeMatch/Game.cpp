#include "Game.h"
#include <iostream>

#include "TextureManager.h"
#include "GemObject.h"
#include "Grid.h"

GemObject* gem;
GemObject* gemTwo;
GemObject* gemThree;
Grid* grid;

SDL_Event Game::event;

//GemObject* GemArrayTest[5] = { gem , gem , gem , gem , gem };

SDL_Texture* TextureBackground;
SDL_Texture* TextureGem;

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

	//gem = new GemObject("textures/BlueGem.png", renderer, 500, 500);
	//gemTwo = new GemObject("textures/GreenGem.png", renderer, 400, 500);
	//gemThree = new GemObject("textures/RedGem.png", renderer, 300, 500);

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
	default:
		break;
	}
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

	//gem->Render();
	//gemTwo->Render();
	//gemThree->Render();
	grid->RenderGrid();

	//GemArrayTest[0]->Render();


	// Thi is the final call, nothing should go below this
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}