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
class Texture;

class Game
{
public:
	Game(Platform* platform);
	~Game();

	bool exitRequested() const;

	void init();
	void tick(double deltaTime);
	void render(double alpha);
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
	Texture* mTexture;

	void loadResources();
	void update(double deltaTime);

#ifdef _DEBUG
	void debugUI();
#endif
};

#endif // GAME_H