#pragma once
#include "SDL.h"
#include <string>
#include <map>

class TextureManager
{
public:

	// Load texture from file
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	// Draw still image
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	// Draw animation
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	// Clear textures from map
	void clearFromTextureMap(std::string id);

	std::map<std::string, SDL_Texture*> m_textureMap;

	static TextureManager* Instance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new TextureManager();
			return pInstance;
		}
		return pInstance;
	}

private:

	// Constructor
	TextureManager() {}
	static class TextureManager* pInstance;
};

