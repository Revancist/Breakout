#include "TextureManager.h"
#include <SDL_image.h>

TextureManager* TextureManager::pInstance = nullptr;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	// Add texture to the list
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	// Texture loading failed
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	// Create source and destination rectangles
	SDL_Rect srcRect;
	SDL_Rect destRect;

	// Set source rectangle coordinates to 0
	srcRect.x = 0;
	srcRect.y = 0;

	// Set size of drawn image
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	// Set destination rectangle coordinates
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	// Create source and destination rectangles
	SDL_Rect srcRect;
	SDL_Rect destRect;

	// Set source rectangle coordinates to correct part of the animation sprite
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);

	// Set size of drawn animation sprite
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	// Set destination rectangle coordinates
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}
