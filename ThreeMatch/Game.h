#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GemObject.h"
#include "SDL_ttf.h"

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents(); // Handle user input
	void hanldeMouseClick(); // Handle mouse clicks
	void handleGemRemove(int xPos, int yPos);
	void handleGemSwap(); // Tell gems to swap (dance time!) TODO: remove
	void update();	// Update game elements
	void render();	// Render to clean
	void clean(); // Clean game memory
	void restartGame();

	bool isRunning() { return running; }; // returns running state
	static SDL_Event event; // event variable 

private:
	bool running;
	bool hasGameEnded = false;
	
	int cnt = 0;
	int gameCount = 0;

	int gemSize = 96;
	int gridSize = 96 * 10;
	
	// some variable to help swap gems
	// -1 will be the unset state, can use this for checking first / second click
	int firstClickGemPosX = -1;
	int firstClickGemPosY = -1;

	int secondClickGemPosX = -1;
	int secondClickGemPosY = -1;

	class Grid* grid;
	class TextDrawer* ScoreText;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* TextureBackground;
	SDL_Texture* EndScreen;

	TTF_Font* FontAreal = TTF_OpenFont("font/arial.ttf", 24);
	SDL_Color FontWhite = { 255, 255, 255 };
};