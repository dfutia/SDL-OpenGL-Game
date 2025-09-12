#ifndef CAMERA_H
#define CAMERA_H

#include "renderer/camerabehavior.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, float fov, float aspectRatio, float nearPlane, float farPlane)
		: mPosition(position), mFront(front), mUp(up), mFOV(fov), mAspectRatio(aspectRatio), mNearPlane(nearPlane), mFarPlane(farPlane)
	{}

	~Camera() = default;

	void update(double deltaTime)
	{
		if (mBehavior)
		{
			mBehavior->Update(*this, deltaTime);
		}
	}

	void setBehavior(CameraBehavior* behavior) { mBehavior = behavior; }
	void setPosition(const glm::vec3& position) { mPosition = position; }
	void setFront(const glm::vec3& front) { mFront = front; }
	void setUp(const glm::vec3& up) { mUp = up; }
	void setRight(const glm::vec3& right) { mRight = right; }
	void setAspectRatio(float aspectRatio) { mAspectRatio = aspectRatio; }

	const glm::vec3& getPosition() const { return mPosition; }
	const glm::vec3& getFront() const { return mFront; }
	const glm::vec3& getUp() const { return mUp; }
	const glm::vec3& getRight() const { return mRight; }
	float getFOV() const { return mFOV; }
	float getAspectRatio() const { return mAspectRatio; }
	float getNearPlane() const { return mNearPlane; }
	float getFarPlane() const { return mFarPlane; }
	glm::mat4 getViewMatrix() const { return glm::lookAt(mPosition, mPosition + mFront, mUp); }
	glm::mat4 getProjectionMatrix() const { return glm::perspective(glm::radians(mFOV), mAspectRatio, mNearPlane, mFarPlane); }
private:
	glm::vec3 mPosition;
	glm::vec3 mFront;
	glm::vec3 mUp;
	glm::vec3 mRight;

	float mFOV, mAspectRatio, mNearPlane, mFarPlane;

	CameraBehavior* mBehavior;
};

#endif // CAMERA_H