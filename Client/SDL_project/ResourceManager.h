#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include "Atlas.h"

class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture2D> Textures;
	static std::map<std::string, Atlas> Atlass;

	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	// Retrieves a stored sader
	static Shader   GetShader(std::string name);
	// Loads (and generates) a texture from file
	static Texture2D LoadTexture(const std::string& file);
	static Texture2D CreateTextureFromAtlas(Atlas& atlas, int index);
	static Texture2D GetAtlasTexture(std::string atlasName, int index);
	// Retrieves a stored texture
	static Texture2D GetTexture(std::string name);


	static Atlas GetAtlas(std::string name);
	//! Loads and generates an atlas file
	static Atlas LoadAtlas(std::string name, std::string file, int tileWidth, int tileSize);
	//! Loads and generates an atlas file
	static Atlas LoadAtlas(std::string name, std::string file, int tileWidth, glm::ivec2 spriteSize);
	// Properly de-allocates all loaded resources
	static void  Clear();

private:
	
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() { }
	// Loads and generates a shader from file
	static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	// Loads a single texture from file
	static Texture2D loadTextureFromFile(std::string file);
};


