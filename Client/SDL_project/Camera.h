#pragma once
class Camera
{
public:
	Camera::Camera();
	Camera::~Camera();
	//! Get positions
	float getX() { return X; }
	float getY() { return Y; }
	//! Set positions
	float setX(float newX) { return X = newX; }
	float setY(float newY) { return Y = newY; }
	void SetPos(float x, float y);

	//! Get and set speeds
	float getCameraSpeed() { return cameraSpeed; }
	float setCameraSpeed(float newSpeed) { return cameraSpeed = newSpeed; }

	glm::vec2 windowSize;
	glm::vec2 ChunksOnScreen;
	glm::vec2 mouse_position;

	//! Lerp to target
	void Camera::Lerp_To(glm::vec2 target, float increment);

	glm::vec2 getPosition() { return { X, Y }; }

private:
	float X;
	float Y;

	float cameraSpeed = 0.5;



};


