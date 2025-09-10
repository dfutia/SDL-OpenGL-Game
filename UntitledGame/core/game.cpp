#include "core/game.h"
#include "core/input.h"
#include "core/world.h"

#include "platform/sdl/sdlwindow.h"
#include "platform/sdl/sdlinput.h"

#include "platform/gl/glrenderer.h"

Game::~Game()
{
	delete mWorld;
	delete mRenderer;
	delete mInput;
	delete mWindow;
}

bool Game::exitRequested() const
{
	return mInput->exitRequested();
}

void Game::loadResources()
{
}

void Game::init()
{
	mWindow = new SDLWindow;
	mInput = new SDLInput();
	mRenderer = new GLRenderer(mWindow);
	mWorld = new World();

	loadResources();
}

void Game::tick()
{
	mInput->pollInput();
	update();
	mRenderer->beginFrame();
	render();
	mRenderer->endFrame();
}

void Game::update()
{
}

void Game::render()
{
}