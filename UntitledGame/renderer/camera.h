#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, float fov, float aspectRatio, float nearPlane, float farPlane)
		: mPosition(position), mFront(front), mUp(up), mFOV(fov), mAspectRatio(aspectRatio), mNearPlane(nearPlane), mFarPlane(farPlane)
	{}

	~Camera() = default;

	glm::mat4 getViewMatrix() const
	{
		return glm::lookAt(mPosition, mPosition + mFront, mUp);
	}

	glm::mat4 getProjectionMatrix() const
	{
		return glm::perspective(glm::radians(mFOV), mAspectRatio, mNearPlane, mFarPlane);
	}
private:
	glm::vec3 mPosition, mFront, mUp;
	float mFOV, mAspectRatio, mNearPlane, mFarPlane;
};

#endif // CAMERA_H