#pragma once

//! Loads and renders images in the window
/*!
This class is used for all the images in the game. It loads textures from a given file location 
and can alter the image transparency if the image is a PNG.
*/
class Texture
{
public:
	//! A constructor
	/*!
	Requires a file path to load the image from
	*/
	Texture(const std::string& fileName);
	//! A destructor
	~Texture();

	//! Loads the texture
	SDL_Texture* getTexture() { return texture; }
	

	//! Renders the image in the window
	void render(SDL_Renderer* renderer, int x, int y, int width, int height);
	//! Render an Atlas
	void renderAtlas(SDL_Renderer* renderer, int x, int y, int width, int height, int index);
	//! Renders the image in the window with rotation
	void renderRotation(SDL_Renderer* renderer, int x, int y, int width, int height, int angle);
	//! Renders  the animation
	void renderAnim(SDL_Renderer* renderer, int sourceX, int sourceY, int destX, int destY, int pixelSize, int renderSize);
	void renderAnim(SDL_Renderer* renderer, int sourceX, int sourceY, int destX, int destY, int pixelSize, int renderSize, bool flipHorizontal);
	//! Render light
	void renderLight(SDL_Renderer* renderer, int sourceX, int sourceY, int destX, int destY, int pixelSize, int renderSize);
	//! Alters the alpha value of the image to make it appear transparent in the window
	void alterTransparency(int transparencyLevel);
	//! Alters the r,g,b colours of the texture
	void alterTextureColour(int r, int g, int b);
	void alterTextureColour(vec3& color);
	void alterTextureColour(vec3& color, int hueChange);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);
	//! Set Atlas type -- Type 0 = 128px / no border -- Type 1 = 16bit / 1px border
	char setAtlasType(char type) { return atlasType = type; }
	//! Set Atlas tile size
	int setTileSize(int size ) { return atlasTileSize = size; }
	//! Set Atlas tile width number
	int setTileWidth(int width) { return atlasTileWidth = width; }

	SDL_Rect& getRect() { return dstrect; }
private:
	//! The width of tile sets
	int atlasTileWidth = 16;
	//! Atlas tile size
	int atlasTileSize = 16;
	//! Atlas type -- Type 0 = no border -- Type 1 = 1px border -- Type 2 = 32bit no border
	char atlasType;
	//! The image location
	std::string fileName;
	//! Pointer to the SDL Texture
	SDL_Texture* texture;

	SDL_Rect srcrect;
	SDL_Rect dstrect;
};
