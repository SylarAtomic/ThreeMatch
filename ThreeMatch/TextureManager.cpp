#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texturePath, SDL_Renderer* renderer)
{
	// create a temp surface to hold the loaded texture
	SDL_Surface* tempSurface = IMG_Load(texturePath);
	// create the acture texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	// clean up the temp surface
	SDL_FreeSurface(tempSurface);

	// finally return the texture
	return texture;
}