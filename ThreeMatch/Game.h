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


};