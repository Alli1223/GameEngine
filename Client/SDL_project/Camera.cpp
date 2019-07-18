#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{

}

Camera::~Camera()
{

}


void Camera::Lerp_To(glm::vec2 target, float increment)
{
	float lerp_x = X + (target.x - X) * increment;
	float lerp_y = Y + (target.y - Y) * increment;

	X = lerp_x;
	Y = lerp_y;
}

void Camera::SetPos(float x, float y) {
	X = x;
	Y = y;
}
