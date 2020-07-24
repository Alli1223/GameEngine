#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Light.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct GLCharacter {
	Texture2D texture;   // Glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

struct GL_Sprite
{
	std::vector<Texture2D> g_Sprite;
	std::vector<Texture2D> g_Normal;
	std::vector <glm::vec2> g_Pos;
	std::vector <glm::vec2> g_Size;
	std::vector <GLfloat> g_Rotate;
	std::vector <GLfloat> g_Transparency;
	std::vector <glm::vec3> g_Colour;
	std::vector <std::pair<bool, bool>> g_flip;
	std::vector <std::vector<glm::vec3>> g_light_pos;
	std::vector <std::vector<glm::vec3>> g_light_col;
};

class GL_Renderer
{
public:
	//! Constructor
	GL_Renderer();
	//! Destructor
	~GL_Renderer();


	//! Update the renderers lights
	void RenderLine(glm::vec2 point1, glm::vec2 point2);
	//! Render a texture
	//! Render an in game sprite without lighting
	void RenderSprite(Texture2D &texture, glm::vec2& position, glm::vec2& size = glm::vec2(10, 10), GLfloat rotate = 0.0f, GLfloat transparency = 255.0f, glm::vec3& color = glm::vec3(1.0f), std::pair<bool, bool> flipSprite = { false, false });
	void RenderAllLayers();
	//! Render a GUI object
	void RenderGUI(Texture2D &texture, glm::vec2& position, glm::vec2& size, GLfloat rotate, GLfloat transparency, glm::vec3& color, std::pair<bool, bool> flipSprite);
	void SetProjectionMatrix();

	//! Render with normals
	void RenderSpriteLighting(Texture2D &texture, Texture2D &normals, glm::vec2& position, glm::vec2& size, GLfloat rotate, GLfloat transparency, int renderLayer, glm::vec3& color, std::pair<bool, bool> flipSprite);
	void RenderShadows(Texture2D& texture, glm::vec2& position, glm::vec2& size, glm::vec2  resolution);

	//! Render text to the screen
	void RenderText(std::string text, glm::vec2 position, glm::vec2 size, glm::vec2 textSize, glm::vec3 color);

	//! Render outline
	void RenderOutline(Texture2D& texture, glm::vec2& position, glm::vec2& size, GLfloat rotate, GLfloat transparency, glm::vec3& color, std::pair<bool, bool> flipSprite);

	//! Create a map of all the ascii textures
	void CreateTextCharacterAtals();

	//! Map of all the lights
	std::map<int, Light> lights;

	//! Screen resolution
	glm::vec2 resolution;

	//! Map of all the render layers
	std::map<int, GL_Sprite> layers;
	//! Map of object outlines to render on highlighted objects
	std::map<int, GL_Sprite> outlines;

	//! Used for calculating whether the sprite should be rendererd before or after the player 
	glm::vec2 playerPosition;

	// OLD
	void RenderUpperSprites();

	bool isPlayerInWorld = true;

	//! Texture for cell highlught
	Texture2D farmingHighlight;
	
	//! Time of day (0.0 night, 1.0 day)
	float timeOfDay;

	//! The games camera
	Camera camera;

	//! Cell size of current level
	int currentInstanceCellSize = 100;
private:

	//! TODO
	void RenderOutlines(Texture2D& texture, glm::vec2& position, glm::vec2& size, GLfloat rotate, GLfloat transparency, glm::vec3& color, std::pair<bool, bool> flipSprite);
	//! Initilise renderer
	void init();
	// Init shadows shader FBO
	GLuint fbo;
	//! Quad Vertex Array Object
	GLuint quadVAO;
	//! Sprite shader
	Shader spriteShader;
	Shader GUIShader;
	Shader lightingShader;
	Shader textShader;
	Shader outlineShader;

	GLuint vertexbuffer;

	std::vector<glm::vec3> light_positions;
	std::vector<glm::vec3> light_colours;

	//! List of ascii characters 
	std::map<GLchar, GLCharacter> GLCharacters;
	GLuint VAO, VBO;

	
	const std::string TerrainSprite = "Resources\\Sprites\\Terrain\\";
	const std::string SpriteSheets = "Resources\\Sprites\\SpriteSheets\\";
	const std::string CropSprites = "Resources\\Sprites\\Crops\\";
	int g_i = 0;
};

