#include "stdafx.h"
#include "GL_Renderer.h"

void GL_Renderer::init()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	timeOfDay = 0.5;

	static const GLfloat g_vertex_buffer_data[] = {
			0.0f,  1.0f, 0.0f,
			0.0f,  0.0f, 0.0f
	};


	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

GL_Renderer::GL_Renderer()
{
	this->init();
	this->spriteShader = ResourceManager::LoadShader("Shaders\\vert.glsl", "Shaders\\frag.glsl", nullptr, "shader");
	this->GUIShader = ResourceManager::LoadShader("Shaders\\GUI\\vert.glsl", "Shaders\\GUI\\frag.glsl", nullptr, "GUIShader");
	this->lightingShader = ResourceManager::LoadShader("Shaders\\v_2DLightingShader.glsl", "Shaders\\f_2DLightingShader.glsl", nullptr, "normalShader");
	this->shadowShader = ResourceManager::LoadShader("Shaders\\shadowVertShader.glsl", "Shaders\\shadowFragShader.glsl", nullptr, "shadowShader");
	this->outlineShader = ResourceManager::LoadShader("Shaders\\Outline\\vert.glsl", "Shaders\\Outline\\frag.glsl", nullptr, "outlineShader");
	this->textShader = ResourceManager::LoadShader("Shaders\\Text\\vert.glsl", "Shaders\\Text\\frag.glsl", nullptr, "textShader");

	ResourceManager::LoadAtlas("roguelike", SpriteSheets + "roguelikeSheet_transparent.png", 56, 16);
	ResourceManager::LoadAtlas("roguelike_normal", SpriteSheets + "roguelikeSheet_transparent_normal.png", 56, 16);

	ResourceManager::LoadAtlas("rpgSprites", SpriteSheets + "rpg_sprites.png", 31, 31);
	ResourceManager::LoadAtlas("flowers", SpriteSheets + "flowers.png", 15, 31);
	ResourceManager::LoadAtlas("flowers_normal", SpriteSheets + "flowers_normal.png", 15, 31);

	ResourceManager::LoadAtlas("spring_dirt_1", TerrainSprite + "Spring\\spring_dirt_1.png", 6, 63);
	ResourceManager::LoadAtlas("spring_dirt_1_normal", TerrainSprite + "Spring\\spring_dirt_1_normal.png", 6, 63);
	ResourceManager::LoadAtlas("spring_dirt_2", TerrainSprite + "Spring\\spring_dirt_2.png", 6, 63);
	//ResourceManager::LoadAtlas("spring_grass_light", TerrainSprite + "Terrain.fw2.png", 8, 15);
	//ResourceManager::LoadAtlas("spring_grass_light_normal", TerrainSprite + "Terrain.fw2.png", 8, 15);
	ResourceManager::LoadAtlas("spring_grass_light", TerrainSprite + "Spring\\spring_grass_light.png", 6, 63);
	ResourceManager::LoadAtlas("spring_grass_light_normal", TerrainSprite + "Spring\\spring_grass_normal.png", 6, 63);
	ResourceManager::LoadAtlas("spring_grass_dark", TerrainSprite + "spring_grass_dark.png", 6, 63);
	ResourceManager::LoadAtlas("spring_grass_dark_normal", TerrainSprite + "Spring\\spring_grass_normal.png", 6, 63);

	ResourceManager::LoadAtlas("spring_water", TerrainSprite + "Spring\\water_spring.png", 6, 63);
	ResourceManager::LoadAtlas("spring_water_normal", TerrainSprite + "Spring\\spring_dirt_1_normal.png", 6, 63);

	// Ground sprites
	ResourceManager::LoadAtlas("autumn_ground", TerrainSprite + "Ground\\Autumn_tilesheet.png", 27, 63);
	ResourceManager::LoadAtlas("spring_ground", TerrainSprite + "Ground\\Spring_tilesheet.png", 27, 63);
	ResourceManager::LoadAtlas("summer_ground", TerrainSprite + "Ground\\Summer_tilesheet.png", 21, 63);
	ResourceManager::LoadAtlas("winter_ground", TerrainSprite + "Ground\\Winter_tilesheet.png", 33, 63);
	// Ground Normals
	ResourceManager::LoadAtlas("autumn_ground_normal", TerrainSprite + "Ground\\Autumn_tilesheet_normal.png", 27, 63);
	ResourceManager::LoadAtlas("spring_ground_normal", TerrainSprite + "Ground\\Spring_tilesheet_normal.png", 27, 63);
	ResourceManager::LoadAtlas("summer_ground_normal", TerrainSprite + "Ground\\Summer_tilesheet_normal.png", 21, 63);
	ResourceManager::LoadAtlas("winter_ground_normal", TerrainSprite + "Ground\\Winter_tilesheet_normal.png", 33, 63);

	ResourceManager::LoadAtlas("rocks", TerrainSprite + "rocks.png", 4, 63);	// Rocks
	ResourceManager::LoadAtlas("rocks_normal", TerrainSprite + "rocks_normal.png", 4, 63);	// Rocks normals
	ResourceManager::LoadAtlas("paths", TerrainSprite + "paths.png", 4, 63);	// Paths
	ResourceManager::LoadAtlas("paths_normal", TerrainSprite + "paths_normal.png", 4, 63);	// Paths normals
	ResourceManager::LoadAtlas("water_spriteSheet", TerrainSprite + "water_animation.png", 17, 63);	// Paths normals
	ResourceManager::LoadAtlas("water_spriteSheet_normal", TerrainSprite + "water_animation_normal.png", 17, 63);	// Paths normals

	ResourceManager::LoadAtlas("crops", SpriteSheets + "crops.png", 8, 31);
	ResourceManager::LoadAtlas("tillage", TerrainSprite + "tilled_soil.png", 5, 31);
	ResourceManager::LoadAtlas("seedBags", CropSprites + "Seedbags.png", 9, 31);

	ResourceManager::LoadAtlas("lavender", CropSprites + "lavender.png", 12, { 31, 63 });
	ResourceManager::LoadAtlas("lavender_normal", CropSprites + "lavender.png", 12, { 31, 63 });
	ResourceManager::LoadAtlas("sunflower", CropSprites + "Sunflower.png", 12, {31, 63});
}




void GL_Renderer::CreateTextCharacterAtals()
{
	// FreeType
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, "Resources\\Fonts\\pixel.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		Texture2D texture;
		//glGenTextures(1, &texture.ID);
		texture.Image_Format = GL_RED;
		texture.Internal_Format = GL_RED;
		texture.Filter_Max = GL_LINEAR;
		texture.Filter_Min = GL_LINEAR;
		texture.Wrap_S = GL_CLAMP_TO_EDGE;
		texture.Wrap_T = GL_CLAMP_TO_EDGE;
		texture.Generate(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

		//// Now store character for later use
		GLCharacter character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		GLCharacters.insert(std::pair<GLchar, GLCharacter>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void GL_Renderer::RenderText(std::string text, glm::vec2 position, glm::vec2 size, glm::vec2 textSize, glm::vec3 color)
{

	// Iterate through all characters
	std::string::const_iterator c;
	vec2 posSize = position + size;
	int textIterCount = 0; 
	std::string restOfWords; // for not creating this for each word
	for (c = text.begin(); c != text.end(); c++)
	{
		GLCharacter& ch = GLCharacters[*c];


		// Loop through the string and get the next space
		// If the next space is greater than posSize
		// go to next level
		if (text.find(" ") != std::string::npos)
		{
			restOfWords = text.substr(textIterCount); // get this Pos till end
			int nextSpace = restOfWords.find_first_of(" "); // Get the next space 

			int xp = position.x + ch.Bearing.x * textSize.x;;
			for (int i = 0; i < nextSpace; i++)
				if (xp < posSize.x) // if the word doesnt go over the width
					xp += (ch.Advance >> 6) * textSize.x;
				else // next line
				{
					position.x -= size.x;
					position.y += (ch.Size.y * 2) * textSize.y;
					break;
				}
		}

		GLfloat xpos = position.x + ch.Bearing.x * textSize.x;
		GLfloat ypos = position.y - ch.Bearing.y * textSize.y;
		

		GLfloat w = ch.Size.x * textSize.x;
		GLfloat h = ch.Size.y * textSize.y;

		vec2 size = { w,h };
		this->textShader.Use();
		//// Prepare transformations
		vec2 posi = { xpos, ypos };
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(posi, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
		model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale	
		this->textShader.SetMatrix4("model", model);

		// Set transparency
		this->textShader.SetFloat("transparency", 1.0f);
		this->textShader.SetVector3f("textColour", color);
	
		glActiveTexture(GL_TEXTURE0);
		ch.texture.Bind();
		
		// Render glyph texture over quad
		glBindVertexArray(this->quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);


		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		position.x += (ch.Advance >> 6) * textSize.x; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		textIterCount++;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}
void GL_Renderer::SetProjectionMatrix()
{

	resolution = camera.windowSize;
	// Projection matrix
	float aspect = (float)camera.windowSize.x / (float)camera.windowSize.y;
										
	glm::mat4 projection = glm::ortho(0.0f, (float)camera.windowSize.x, (float)camera.windowSize.y, 0.0f, -10.0f, 10.0f); // set up projection matrix (left, right, bottom, top, near, far)

	glOrtho(0, (float)camera.windowSize.x, (float)camera.windowSize.y, 0, 0.0f, 100.0f); // might need?
	//glLightfv
	ResourceManager::GetShader("shader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("shader").SetMatrix4("projection", projection);

	ResourceManager::GetShader("lightShader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("lightShader").SetMatrix4("projection", projection);

	ResourceManager::GetShader("normalShader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("normalShader").SetMatrix4("projection", projection);

	ResourceManager::GetShader("shadowShader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("shadowShader").SetMatrix4("projection", projection);

	ResourceManager::GetShader("outlineShader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("outlineShader").SetMatrix4("projection", projection);

	ResourceManager::GetShader("GUIShader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("GUIShader").SetMatrix4("projection", projection);

	ResourceManager::GetShader("textShader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("textShader").SetMatrix4("projection", projection);
}

void GL_Renderer::Clear()
{
	lights.erase(lights.begin(), lights.end());
	shadows.erase(shadows.begin(), shadows.end());
	outlines.erase(outlines.begin(), outlines.end());
	layers.erase(layers.begin(), layers.end());
}

GL_Renderer::~GL_Renderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void GL_Renderer::RenderLine(glm::vec2 point1, glm::vec2 point2)
{
	this->GUIShader.Use();
	//// Prepare transformations
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(point1, 0.0f));


	model = glm::scale(model, glm::vec3(0.5,0.5, 1.0f)); // Last scale	


	this->spriteShader.SetMatrix4("model", model);
	// Lighting
	this->spriteShader.SetVector3f("ambientLight", { 0.9, 0.9, 0.9 });
	//this->spriteShader.SetVector2f("lightPos", camera.mouse_position / 100.0f);

	//this->spriteShader.SetVector2f("objectPos", position / 100.0f);

	// Set transparency
	this->spriteShader.SetFloat("transparency", 1.0f);

	// 1rst attribute buffer : vertices
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//
	//glVertexAttribPointer(
	//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	//	2,                  // size
	//	GL_FLOAT,           // type
	//	GL_FALSE,           // normalized?
	//	0,                  // stride
	//	(void*)0            // array buffer offset
	//);
	//
	//// Draw the line !
	//glDrawArrays(GL_LINES, 0, 2); // 2 indices for the 2 end points of 1 line

	glBindVertexArray(vertexbuffer);

	glLineWidth(4);
	glDrawArrays(GL_LINE_STRIP, 0, 2);

	glBindVertexArray(0);


	//glBindVertexArray(this->vertexbuffer);
	//glDrawArrays(GL_LINES, 0, 2);
	//glBindVertexArray(0);

}

//! Render the sprite
void GL_Renderer::RenderSprite(Texture2D &texture, glm::vec2& position, glm::vec2& size, GLfloat rotate, GLfloat transparency, glm::vec3& color, std::pair<bool, bool> flipSprite)
{
	this->spriteShader.Use();

	// Prepare transformations
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position  - camera.getPosition(), 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	if (flipSprite.first)
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f)); // flip horizontally
	else if (flipSprite.second)
		model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f)); // flip vertically
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale	

	this->spriteShader.SetMatrix4("model", model);

	// Lighting
	this->spriteShader.SetVector3f("ambientLight", { 0.9, 0.9, 0.9 });

	// Set transparency
	this->spriteShader.SetFloat("transparency", transparency);

	// Render textured quad
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

//! Render a sprite to screen
void GL_Renderer::RenderGUI(Texture2D &texture, glm::vec2& position, glm::vec2& size, GLfloat rotate, GLfloat transparency, glm::vec3& color, std::pair<bool, bool> flipSprite)
{
	this->GUIShader.Use();

	// Prepare transformations
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position - (size / 2.0f) , 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	if (flipSprite.first)
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f)); // flip horizontally
	else if (flipSprite.second)
		model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f)); // flip vertically
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale	

	this->GUIShader.SetMatrix4("model", model);

	// Set Colour (and convert to 0.0/1.0 rather than 0/255)
	if (color.r == 0.0f && color.g == 0.0f && color.b == 0.0f)
		color = { 1.0f,1.0f,1.0f };

	this->GUIShader.SetVector3f("imageColour", color);
	// Set transparency
	this->GUIShader.SetFloat("Transparency", transparency);

	// Render textured quad
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void GL_Renderer::RenderUpperSprites()
{
	//for (int i = 0; i < g_Sprite.size(); i++)
	//{
	//
	//	RenderSpriteLighting(g_Sprite[i], g_Normal[i], g_Pos[i], g_Size[i], g_Rotate[i], g_Transparency[i], 0.26f, g_Colour[i], g_flip[i]);
	//}
	//g_Sprite.clear();
	//g_Normal.clear();
	//g_Pos.clear();
	//g_Size.clear();
	//g_Rotate.clear();
	//g_Transparency.clear();
	//g_Colour.clear();
	//g_flip.clear();
	
}
void GL_Renderer::RenderAllLayers()
{
	for (auto layer : layers)
	{
		if (layer.first == 0)
		{
			for (int i = 0; i < layer.second.g_Sprite.size(); i++)
				RenderSpriteLighting(layer.second.g_Sprite[i], layer.second.g_Normal[i], layer.second.g_Pos[i], layer.second.g_Size[i], layer.second.g_Rotate[i], layer.second.g_Transparency[i], -1, layer.second.g_Colour[i], layer.second.g_flip[i]);
		}
		else if (layer.first == 1)
		{
			for (int i = 0; i < layer.second.g_Sprite.size(); i++)
				RenderSpriteLighting(layer.second.g_Sprite[i], layer.second.g_Normal[i], layer.second.g_Pos[i], layer.second.g_Size[i], layer.second.g_Rotate[i], layer.second.g_Transparency[i], -1, layer.second.g_Colour[i], layer.second.g_flip[i]);
		}
		else if (layer.first == 2)
		{
			for (int i = 0; i < layer.second.g_Sprite.size(); i++)
				RenderSpriteLighting(layer.second.g_Sprite[i], layer.second.g_Normal[i], layer.second.g_Pos[i], layer.second.g_Size[i], layer.second.g_Rotate[i], layer.second.g_Transparency[i], -1, layer.second.g_Colour[i], layer.second.g_flip[i]);
		}
		//glDisable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_MIN);
		//GLclampf red = 1.0f;
		//glBlendColor(red, red, red, GL_SRC_ALPHA);
		//glBlendEquation(GL_FUNC_SUBTRACT);
		for (auto shdow : shadows)
		{
			for (int i = 0; i < shdow.second.g_Sprite.size(); i++)
				RenderShadow(shdow.second.g_Sprite[i], shdow.second.g_Pos[i], shdow.second.g_Size[i], shdow.second.g_flip[i]);
		}	
		//glBlendEquation(GL_FUNC_ADD);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (layer.first == 3)
		{
			for (int i = 0; i < layer.second.g_Sprite.size(); i++)
				RenderSpriteLighting(layer.second.g_Sprite[i], layer.second.g_Normal[i], layer.second.g_Pos[i], layer.second.g_Size[i], layer.second.g_Rotate[i], layer.second.g_Transparency[i], -1, layer.second.g_Colour[i], layer.second.g_flip[i]);

		}
		else if (layer.first == 4)
		{
			for (int i = 0; i < layer.second.g_Sprite.size(); i++)
				RenderSpriteLighting(layer.second.g_Sprite[i], layer.second.g_Normal[i], layer.second.g_Pos[i], layer.second.g_Size[i], layer.second.g_Rotate[i], layer.second.g_Transparency[i], -1, layer.second.g_Colour[i], layer.second.g_flip[i]);
		}
	}
	for (auto outline : outlines)
	{
		for (int i = 0; i < outline.second.g_Sprite.size(); i++)
			RenderOutlines(outline.second.g_Sprite[i], outline.second.g_Pos[i], outline.second.g_Size[i], outline.second.g_Rotate[i], outline.second.g_Transparency[i], outline.second.g_Colour[i], outline.second.g_flip[i]);
	}

	Clear();
	//outlines.erase(outlines.begin(), outlines.end());
	//shadows.erase(shadows.begin(), shadows.end());
	//layers.erase(layers.begin(), layers.end());
}

void GL_Renderer::RenderSpriteLighting(Texture2D &texture, Texture2D &normals, glm::vec2& position, glm::vec2& size, GLfloat rotate, GLfloat transparency, int renderLayer, glm::vec3& color, std::pair<bool, bool> flipSprite)
{
	// If on same layer as player determine whether to render player on top or below object
	if (renderLayer == 3)
	{
		if (GameSettings::currentInstance->I_player.getPosition().y < position.y)
		{
			renderLayer = 3;
		}
		else
			renderLayer = 2;
	}

	// Render higher objects later
	if (renderLayer > 0)
	{
		layers[renderLayer].g_Sprite.push_back(texture);
		layers[renderLayer].g_Normal.push_back(normals);
		layers[renderLayer].g_Pos.push_back(position);
		layers[renderLayer].g_Size.push_back(size);
		layers[renderLayer].g_Rotate.push_back(rotate);
		layers[renderLayer].g_Transparency.push_back(transparency);
		layers[renderLayer].g_Colour.push_back(color);
		layers[renderLayer].g_flip.push_back(flipSprite);
	}
	else
	{
		this->lightingShader.Use();

		// Prepare transformations
		glm::mat4 model;
		model = glm::translate(model, glm::vec3((position - size / 2.0f) - camera.getPosition(), 0.0f));  // First translate (transformations are: scale happens first, then rotation and then final translation happens; reversed order)

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
		if(rotate != 0.0f)
			model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
		if (flipSprite.first)
			model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f)); // flip horizontally

		else if (flipSprite.second)
			model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f)); // flip vertically

		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y,0.0f)); // Move origin back
		model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale	

		if (timeOfDay > 0.6)
		{
			lights.erase(lights.begin(), lights.end());
		}

		// Get light positions

		for (auto const& light : lights)
		{
			vec3 pos = light.second.position;
			pos.x -= camera.getPosition().x;
			pos.y -= camera.getPosition().y;


			pos.x = pos.x / resolution.x;
			pos.y = (-pos.y / resolution.y) + 1.0f; // flip the normalized y axis
			//TODO: optimise this to not re-reate the list each frame
			light_positions.push_back(pos);


			vec3 lightColour = { light.second.colour.r, light.second.colour.g, light.second.colour.b };
			light_colours.push_back(lightColour);
		}

		this->lightingShader.SetInteger("UseLights", 1);

		this->lightingShader.SetInteger("TotalLights", lights.size());

		// Set the vectors of light positions and colours
		if (lights.size() > 0)
		{
			this->lightingShader.SetVectorOfVector3f("ColouredLights", light_colours);
			this->lightingShader.SetVectorOfVector3f("LightPositions", light_positions);
		}

		// If the sprite has a set colour then override the default colour
		if (color.r > 0 || color.g > 0 || color.b > 0)
		{
			this->lightingShader.SetInteger("useColorOverride", 1);
			this->lightingShader.SetVector4f("ColorOverride", { color, transparency });
		}
		else
			this->lightingShader.SetInteger("useColorOverride", 0);

		// Set lighting variables
		// Set transparency
		this->lightingShader.SetFloat("Transparency", transparency);
		this->lightingShader.SetMatrix4("model", model);
		this->lightingShader.SetVector2f("Resolution", resolution);
		this->lightingShader.SetVector3f("LightPos", { camera.mouse_position.x / resolution.x, (-camera.mouse_position.y / resolution.y) + 1.0f, 0.15f }); // normalized mouse pos
		this->lightingShader.SetVector4f("LightColor", { 1.0f, 1.0f, 1.0f, 1.0f });
		this->lightingShader.SetVector4f("AmbientColor", { 0.5f, 0.5f, 0.5f, 0.2f });
		this->lightingShader.SetVector3f("Falloff", { 0.4f, 8.0f, 20.0f }); //Z is area (smaller is bigger)
		this->lightingShader.SetTextureLocation("u_normals", 1); //GL_TEXTURE1
		this->lightingShader.SetFloat("TimeOfDay", timeOfDay);

		// Render textured quad
		glActiveTexture(GL_TEXTURE0);
		texture.Bind();

		//normals
		//bind normal map to texture unit 1
		glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, normals.ID);
		normals.Bind();

		glBindVertexArray(this->quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// erase the lights for the next pass through
		light_positions.clear();
		light_colours.clear();
	}
}


void GL_Renderer::RenderShadow(Texture2D& texture, glm::vec2& position, glm::vec2& size, std::pair<bool, bool> flipSprite)
{
	this->shadowShader.Use();
	GLfloat rotate = timeOfDay - 0.5f;
	vec2 offset = { 0.0f, size.y  - size.y / 20.0f };
	// Prepare transformations
	glm::mat4 model;
	model = glm::translate(model, glm::vec3((((position - size / 2.0f)) - camera.getPosition()) + offset, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then final translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.0f, cos(timeOfDay) * (size.y / 2.0f), 0.0f)); // Change height based on time of day

	model = glm::translate(model, glm::vec3(0.5f * size.x, 1.0f, 0.0f)); // Move origin of rotation to center of quad

	if (flipSprite.first)
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f)); // flip horizontally
	if (!flipSprite.second)
		model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f)); // flip vertically

	model = glm::scale(model, glm::vec3(1.0f, cos(timeOfDay), 1.0f)); // change height based on time of day

	//if (rotate != 0.0f)
		//model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	
	//model = glm::scale(model, glm::vec3(size / 2.0f, 1.0f)); // Reduce size of shadow

	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale	

	//model = glm::translate(model, glm::vec3((sin(timeOfDay) /10.0f), 0.0f, 0.0f)); // Move origin back
	// Skew
	this->shadowShader.SetVector2f("skew", { 0.0f, 0.0f });

	if (timeOfDay > 0.6)
	{
		//lights.erase(lights.begin(), lights.end());
	}


	// TODO: create more shadows for each nearby lightsource
	// Get light positions

	//for (auto const& light : lights)
	//{
	//	//vec3 pos = light.second.position;
	//	//pos.x -= camera.getPosition().x;
	//	//pos.y -= camera.getPosition().y;
	//	//
	//	//
	//	//pos.x = pos.x / resolution.x;
	//	//pos.y = (-pos.y / resolution.y) + 1.0f; // flip the normalized y axis
	//	////TODO: optimise this to not re-reate the list each frame
	//	//light_positions.push_back(pos);
	//	//
	//	//
	//	//vec3 lightColour = { light.second.colour.r, light.second.colour.g, light.second.colour.b };
	//	//light_colours.push_back(lightColour);
	//}

	//this->lightingShader.SetInteger("UseLights", 1);
	//this->lightingShader.SetInteger("TotalLights", lights.size());

	// Set the vectors of light positions and colours
	//if (lights.size() > 0)
	//{
	//	this->lightingShader.SetVectorOfVector3f("ColouredLights", light_colours);
	//	this->lightingShader.SetVectorOfVector3f("LightPositions", light_positions);
	//}
	//
	//// If the sprite has a set colour then override the default colour
	//if (color.r > 0 || color.g > 0 || color.b > 0)
	//{
	//	this->lightingShader.SetInteger("useColorOverride", 1);
	//	this->lightingShader.SetVector4f("ColorOverride", { color, transparency });
	//}
	//else
	//	this->lightingShader.SetInteger("useColorOverride", 0);

	// Set lighting variables
	// Set transparency
	this->shadowShader.SetFloat("Transparency", min(timeOfDay, 0.3f));
	this->shadowShader.SetMatrix4("model", model);
	//this->shadowShader.SetVector2f("Resolution", resolution); 
	this->shadowShader.SetVector3f("imageColour", { 0.0f,0.0f,0.0f });
	//this->lightingShader.SetVector4f("LightColor", { 1.0f, 1.0f, 1.0f, 1.0f });
	//this->lightingShader.SetVector4f("AmbientColor", { 0.5f, 0.5f, 0.5f, 0.2f });
	//this->lightingShader.SetVector3f("Falloff", { 0.4f, 8.0f, 20.0f }); //Z is area (smaller is bigger)
	//this->lightingShader.SetTextureLocation("u_normals", 1); //GL_TEXTURE1
	//this->shadowShader.SetFloat("TimeOfDay", timeOfDay);

	// Render textured quad
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void GL_Renderer::RenderShadows(Texture2D& texture, glm::vec2& position, glm::vec2& size, std::pair<bool, bool> flipSprite)
{
	int i = shadows.size();
	shadows[i].g_Sprite.push_back(texture);
	shadows[i].g_Pos.push_back(position);
	shadows[i].g_Size.push_back(size);
	shadows[i].g_flip.push_back(flipSprite);
}

void GL_Renderer::RenderOutlines(Texture2D& texture, glm::vec2& position, glm::vec2& size, GLfloat rotate, GLfloat transparency, glm::vec3& color, std::pair<bool, bool> flipSprite)
{
	this->outlineShader.Use();

	// Prepare transformations
	glm::mat4 model;
	model = glm::translate(model, glm::vec3((position - size / 2.0f) - camera.getPosition(), 0.0f));  // First translate (transformations are: scale happens first, then rotation and then final translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	if (rotate != 0.0f)
		model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	if (flipSprite.first)
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f)); // flip horizontally

	else if (flipSprite.second)
		model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f)); // flip vertically

	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale	

	this->outlineShader.SetMatrix4("model", model);


	// Set transparency
	this->outlineShader.SetFloat("Transparency", 0.5f);
	this->outlineShader.SetVector3f("outlineColour", { 0.5f,0.1f,0.8f });


	// Render textured quad
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

}

void GL_Renderer::RenderOutline(Texture2D& texture, glm::vec2& position, glm::vec2& size, GLfloat rotate, GLfloat transparency, glm::vec3& color, std::pair<bool, bool> flipSprite)
{
	int i = outlines.size();
	outlines[i].g_Sprite.push_back(texture);
	outlines[i].g_Pos.push_back(position);
	outlines[i].g_Size.push_back(size);
	outlines[i].g_Rotate.push_back(rotate);
	outlines[i].g_Transparency.push_back(transparency);
	outlines[i].g_Colour.push_back(color);
	outlines[i].g_flip.push_back(flipSprite);
}