#ifndef GAME_H
#define GAME_H

class Window;
class Input;
class Renderer;
class World;

class Game
{public:
	Game() = default;
	~Game();

	bool exitRequested() const;

	void init();
	void tick();

private:
	Window* mWindow;
	Input* mInput;
	Renderer* mRenderer;
	World* mWorld;

	void loadResources();
	void update();
	void render();
};

#endif // GAME_H