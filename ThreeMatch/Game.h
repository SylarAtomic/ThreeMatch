#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GemObject.h"

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents(); // Handle user input
	void hanldeMouseClick(); // Handle mouse clicks
	void handleGemSwap(); // Tell gems to swap (dance time!)
	void update();	// Update game elements
	void render();	// Render to clean
	void clean(); // Clean game memory

	bool isRunning() { return running; };
	static SDL_Event event;

private:
	bool running;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int cnt = 0;

	int gemSize = 96;
	int gridSize = 96 * 10;

	// some variable to help swap gems
	// -1 will be the unset state, can use this for checking first / second click
	int firstClickGemPosX = -1;
	int firstClickGemPosY = -1;

	int secondClickGemPosX = -1;
	int secondClickGemPosY = -1;
};