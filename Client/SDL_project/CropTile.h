#pragma once
#include "GameObject.h"
#include "Crop.h"
class CropTile : public GameObject
{
public:
	CropTile();
	CropTile(glm::ivec2 pos, int size);
	~CropTile();

	std::shared_ptr<Crop> crop;

	enum Orientation
	{
		topLeft,
		topMiddle,
		topRight,
		middleLeft,
		middle,
		middleRight,
		bottomLeft,
		bottomMiddle,
		bottomRight,

		alone,

		verticalMiddle,
		verticalEndTop,
		verticalEndBottom,

		horizontalMiddle,
		horizontalEndLeft,
		horizontalEndRight,

		

	}orientation;

	json getJson();

	void SetOrientation(Orientation orient);

	void Render(GL_Renderer& renderer);

	bool isTilled = false;
	int ID = -1;
};

