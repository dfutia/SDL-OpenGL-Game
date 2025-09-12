#ifndef CAMERA_BEHAVIOR_H
#define CAMERA_BEHAVIOR_H

class Camera;

class CameraBehavior
{
public:
	virtual ~CameraBehavior() = default;
	virtual void Update(Camera& camera, double deltaTime) = 0;
};

class StaticCamera : public CameraBehavior
{
	public:
		void Update(Camera& camera, double deltaTime) override 
		{
		}
};

class DebugCamera : public CameraBehavior
{
	public:
		void Update(Camera& camera, double deltaTime) override;
};

#endif // CAMERA_BEHAVIOR_H