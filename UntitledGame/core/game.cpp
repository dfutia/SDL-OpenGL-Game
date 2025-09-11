#include "core/game.h"
#include "core/input.h"
#include "core/world.h"
#include "core/services.h"

#include "renderer/camera.h"

#include "platform/sdl/sdlplatform.h"
#include "platform/sdl/sdlwindow.h"
#include "platform/sdl/sdlinput.h"

#include "platform/gl/glrenderer.h"

#include <imgui.h>

Game::Game(Platform* platform)
{
	mRenderer = new GLRenderer;
	mWorld = new World;
	mInput = Services::getService<Input>("Input");
}

Game::~Game()
{
	delete mWorld;
	delete mRenderer;
}

bool Game::exitRequested() const
{
	return mInput->exitRequested();
}

void Game::loadResources()
{
	mShaderProgram = mResourceManager->loadShaders("assets/basic.vert", "assets/basic.frag");
}

void Game::init()
{
	loadResources();

	mCamera = new Camera(
		glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		60.0f,
		800.0f / 600.0f,
		0.1f,
		100.0f
	);

	const Vertex cubeVertices[] = {
		// Front face
		{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
		{{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

		// Back face
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
		{{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
		{{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

		// Additional faces... (left, right, top, bottom)
	};

	const unsigned int cubeIndices[] = {
	0, 1, 2, 2, 3, 0,   // Front
	4, 5, 6, 6, 7, 4,   // Back
	// Add indices for other faces...
	};

	mCubeVB = mRenderer->createVertexBuffer(cubeVertices, sizeof(cubeVertices) / sizeof(Vertex));
	mCubeIB = mRenderer->createIndexBuffer(cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int));
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
	ImGui::ShowDemoWindow();

	mRenderer->bindResource(mShaderProgram);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = mCamera->getViewMatrix();
	glm::mat4 projection = mCamera->getProjectionMatrix();
	glm::mat4 mvp = projection * view * model;

	GLint viewProjLoc = glGetUniformLocation(mShaderProgram->getResourceID(), "u_ViewProj");
	GLint modelLoc = glGetUniformLocation(mShaderProgram->getResourceID(), "u_Model");

	glUniformMatrix4fv(viewProjLoc, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

	mRenderer->bindResource(mCubeVB);
	mRenderer->bindResource(mCubeIB);
	glDrawElements(GL_TRIANGLES, mCubeIB->getIndexCount(), GL_UNSIGNED_INT, 0);
	mRenderer->unbindResource(mCubeIB);
	mRenderer->unbindResource(mCubeVB);
	mRenderer->unbindResource(mShaderProgram);
}