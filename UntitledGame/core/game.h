#ifndef GAME_H
#define GAME_H

class Platform;
class Window;
class Input;
class Renderer;
class ResourceManager;
class World;

class Camera;
class VertexBuffer;
class IndexBuffer;
class ShaderProgram;

class Game
{
public:
	Game(Platform* platform);
	~Game();

	bool exitRequested() const;

	void init();
	void tick();

private:
	Window* mWindow;
	Input* mInput;
	Renderer* mRenderer;
	ResourceManager* mResourceManager;
	World* mWorld;

	Camera* mCamera;
	VertexBuffer* mCubeVB;
	IndexBuffer* mCubeIB;
	ShaderProgram* mShaderProgram;

	void loadResources();
	void update();
	void render();
};

#endif // GAME_H