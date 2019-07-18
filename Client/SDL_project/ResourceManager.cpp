#include "stdafx.h"
#include "ResourceManager.h"

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<std::string, Atlas>       ResourceManager::Atlass;


std::string getFileLocation(std::string file)
{
	int last = file.find_last_of(".");
	std::string fileLocation = file.substr(0, last);
	std::string fileFormat = file.substr(last, file.size());
	return fileLocation + "_normal" + fileFormat;
}


Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Atlas ResourceManager::GetAtlas(std::string name)
{
	return Atlass[name];
}
Texture2D ResourceManager::GetAtlasTexture(std::string atlasName, int index)
{
	return CreateTextureFromAtlas(Atlass[atlasName], index);
}

Atlas ResourceManager::LoadAtlas(std::string name, std::string file, int SpritesInWidth, int tileSize)
{
	if (Atlass.count(name) > 0)
		return Atlass.at(name);
	Atlas newAtlas;
	newAtlas.atlasFileLocation = file;
	newAtlas.optionalNormalMapLocation = getFileLocation(file);
	newAtlas.spritesInWitdth = SpritesInWidth;
	newAtlas.atlasTileSize = tileSize;
	Atlass[name] = newAtlas;
	return newAtlas;
}
Atlas ResourceManager::LoadAtlas(std::string name, std::string file, int SpritesInWidth, glm::ivec2 spriteSize)
{
	if (Atlass.count(name) > 0)
		return Atlass.at(name);
	Atlas newAtlas;
	newAtlas.atlasFileLocation = file;
	newAtlas.optionalNormalMapLocation = getFileLocation(file);
	newAtlas.spritesInWitdth = SpritesInWidth;
	newAtlas.spritesWdith = spriteSize.x;
	newAtlas.spritesHeight = spriteSize.y;
	Atlass[name] = newAtlas;
	return newAtlas;
}


Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const std::string& file)
{
	if(Textures.count(file) > 0)
		return Textures[file];
	else
	{
		Textures[file] = loadTextureFromFile(file);
		return Textures[file];
	}
}

Texture2D ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

SDL_Surface* crop_surface(SDL_Surface* sprite_sheet, int x, int y, int width, int height)
{

	SDL_Surface* surface = SDL_CreateRGBSurface(sprite_sheet->flags, width, height, sprite_sheet->format->BitsPerPixel, sprite_sheet->format->Rmask, sprite_sheet->format->Gmask, sprite_sheet->format->Bmask, sprite_sheet->format->Amask);

	SDL_Rect rect = { x, y, width, height };

	SDL_BlitSurface(sprite_sheet, &rect, surface, 0);
	return surface;
}
void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(std::string file)
{
	// Get the texture from file
	SDL_Surface* textureSurface = IMG_Load(file.c_str());
	if (textureSurface == nullptr)
		printf("Error loading texture surface");

	// Create Texture object
	Texture2D texture;
	
	// Now generate texture
	texture.Generate(textureSurface);
	// And finally free image data
	SDL_FreeSurface(textureSurface);
	return texture;
}




Texture2D ResourceManager::CreateTextureFromAtlas(Atlas& atlas, int index)
{
	std::string concatFileName = atlas.atlasFileLocation + "_" + std::to_string(index);
	std::string concatFileNameNormal = atlas.optionalNormalMapLocation + "_" + std::to_string(index);
	// If it has been created before
	if (Textures.count(concatFileName) > 0)
		return Textures.at(concatFileName);
	if (Textures.count(concatFileNameNormal) > 0)
		return Textures.at(concatFileNameNormal);
	else // Create a new texture from the atlas
	{
		int atlasTileWidth = atlas.spritesInWitdth;
		int atlasTileSize = atlas.atlasTileSize;
		int width = atlas.spritesWdith;
		int height = atlas.spritesHeight;
		if (width > 0 && height > 0)
		{

		}
		else
		{
			width = atlas.atlasTileSize;
			height = atlas.atlasTileSize;
		}
		// Get the texture from file
		SDL_Surface* textureSurface;
		try
		{
			textureSurface = IMG_Load(atlas.atlasFileLocation.c_str());
			//SDL_Surface* croppedSurface = SDL_CreateRGBSurface(0,16,16,32,0,0,0,0);
			//croppedSurface = SDL_ConvertSurface(textureSurface, textureSurface->format, NULL);
		}
		catch (std::exception e)
		{
			std::cout << "Error loading texture: " << e.what() << std::endl;
		}
		if (textureSurface == NULL)
		{
			int test = 0;
		}

		SDL_Rect srcrect;
		SDL_Rect dstrect;

		int sourceX = index;
		int sourceY = 0;
		while (index > atlasTileWidth)
		{
			sourceY += height + 1;
			index -= atlasTileWidth + 1;
		}
		sourceX = index * width + index;



		srcrect = { sourceX, sourceY, width, height };
		dstrect.x = 0;
		dstrect.y = 0;
		dstrect.w = width;
		dstrect.h = height;


		SDL_Surface* croppedSurface = crop_surface(textureSurface, sourceX, sourceY, width, height);

		// Create Texture object
		Texture2D texture;
		// Now generate texture
		texture.Generate(croppedSurface);
		//Save the texture for future reference
		Textures[concatFileName] = texture;
		// And finally free image data
		SDL_FreeSurface(textureSurface);
		SDL_FreeSurface(croppedSurface);
		// End
		return texture;

	}
}
