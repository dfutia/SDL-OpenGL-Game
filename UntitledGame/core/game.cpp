#include "core/game.h"
#include "core/input.h"
#include "core/world.h"
#include "core/services.h"

#include "renderer/camera.h"
#include "renderer/camerabehavior.h"

#include "platform/sdl/sdlplatform.h"
#include "platform/sdl/sdlwindow.h"
#include "platform/sdl/sdlinput.h"

#include "platform/gl/glrenderer.h"

#include <imgui.h>

#include <print>

Game::Game(Platform* platform)
{
	mRenderer = new GLRenderer;
	mWorld = new World;
	mResourceManager = new ResourceManager;
	mInput = Services::getService<Input>("Input");
}

Game::~Game()
{
	delete mResourceManager;
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
	mTexture = mResourceManager->loadTexture("assets/container.jpg");
}

void Game::init()
{
	loadResources();

	mCamera = new Camera(
		glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		70.0f,
		1280.0f / 720.0f,
		0.1f,
		1000.0f
	);

	const Vertex cubeVertices[] = {
		// Front (+Z)
		{{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1, 0, 0}, {0, 0}},
		{{ 0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1, 0, 0}, {1, 0}},
		{{ 0.5f,  0.5f,  0.5f}, {0, 0, 1}, {1, 0, 0}, {1, 1}},
		{{-0.5f,  0.5f,  0.5f}, {0, 0, 1}, {1, 0, 0}, {0, 1}},

		// Back (-Z)
		{{ 0.5f, -0.5f, -0.5f}, {0, 0, -1}, {-1, 0, 0}, {0, 0}},
		{{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {-1, 0, 0}, {1, 0}},
		{{-0.5f,  0.5f, -0.5f}, {0, 0, -1}, {-1, 0, 0}, {1, 1}},
		{{ 0.5f,  0.5f, -0.5f}, {0, 0, -1}, {-1, 0, 0}, {0, 1}},

		// Left (-X)
		{{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0, 0, 1}, {0, 0}},
		{{-0.5f, -0.5f,  0.5f}, {-1, 0, 0}, {0, 0, 1}, {1, 0}},
		{{-0.5f,  0.5f,  0.5f}, {-1, 0, 0}, {0, 0, 1}, {1, 1}},
		{{-0.5f,  0.5f, -0.5f}, {-1, 0, 0}, {0, 0, 1}, {0, 1}},

		// Right (+X)
		{{ 0.5f, -0.5f,  0.5f}, {1, 0, 0}, {0, 0, -1}, {0, 0}},
		{{ 0.5f, -0.5f, -0.5f}, {1, 0, 0}, {0, 0, -1}, {1, 0}},
		{{ 0.5f,  0.5f, -0.5f}, {1, 0, 0}, {0, 0, -1}, {1, 1}},
		{{ 0.5f,  0.5f,  0.5f}, {1, 0, 0}, {0, 0, -1}, {0, 1}},

		// Top (+Y)
		{{-0.5f,  0.5f,  0.5f}, {0, 1, 0}, {1, 0, 0}, {0, 0}},
		{{ 0.5f,  0.5f,  0.5f}, {0, 1, 0}, {1, 0, 0}, {1, 0}},
		{{ 0.5f,  0.5f, -0.5f}, {0, 1, 0}, {1, 0, 0}, {1, 1}},
		{{-0.5f,  0.5f, -0.5f}, {0, 1, 0}, {1, 0, 0}, {0, 1}},

		// Bottom (-Y)
		{{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1, 0, 0}, {0, 0}},
		{{ 0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1, 0, 0}, {1, 0}},
		{{ 0.5f, -0.5f,  0.5f}, {0, -1, 0}, {1, 0, 0}, {1, 1}},
		{{-0.5f, -0.5f,  0.5f}, {0, -1, 0}, {1, 0, 0}, {0, 1}},
	};

	const unsigned int cubeIndices[] = {
		// Front
		0,  1,  2,   2,  3,  0,
		// Back
		4,  5,  6,   6,  7,  4,
		// Left
		8,  9, 10,  10, 11,  8,
		// Right
		12, 13, 14,  14, 15, 12,
		// Top
		16, 17, 18,  18, 19, 16,
		// Bottom
		20, 21, 22,  22, 23, 20,
	};

	mCubeVB = mRenderer->createVertexBuffer(cubeVertices, sizeof(cubeVertices) / sizeof(Vertex));
	mCubeIB = mRenderer->createIndexBuffer(cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int));

	mCamera->setBehavior(new DebugCamera);
}

void Game::tick(double deltaTime)
{
	mInput->pollInput();
	update(deltaTime);
}

void Game::update(double deltaTime)
{
	mCamera->update(deltaTime);
}

void Game::render(double alpha)
{
	mRenderer->beginFrame();

#ifdef _DEBUG
	debugUI();
#endif

	mRenderer->bindResource(mShaderProgram);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = mCamera->getViewMatrix();
	glm::mat4 projection = mCamera->getProjectionMatrix();
	glm::mat4 viewProj = projection * view;

	GLint viewProjLoc = glGetUniformLocation(mShaderProgram->getResourceID(), "u_ViewProj");
	GLint modelLoc = glGetUniformLocation(mShaderProgram->getResourceID(), "u_Model");
	GLint textureLoc = glGetUniformLocation(mShaderProgram->getResourceID(), "u_Texture");

	glUniform1i(textureLoc, 0);
	glUniformMatrix4fv(viewProjLoc, 1, GL_FALSE, &viewProj[0][0]);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

	mRenderer->bindTexture(mTexture->getGPUResource(), 0);

	mRenderer->bindResource(mCubeVB);
	mRenderer->bindResource(mCubeIB);
	glDrawElements(GL_TRIANGLES, mCubeIB->getIndexCount(), GL_UNSIGNED_INT, 0);
	mRenderer->unbindResource(mCubeIB);
	mRenderer->unbindResource(mCubeVB);
	mRenderer->unbindResource(mShaderProgram);
	mRenderer->endFrame();
}

#ifdef _DEBUG
void Game::debugUI()
{
	//ImGui::ShowDemoWindow();

	if (ImGui::Begin("Camera"))
	{
		glm::vec3 camPos = mCamera->getPosition();
		ImGui::Text("Position: (%.2f, %.2f, %.2f)", camPos.x, camPos.y, camPos.z);
		glm::vec3 camFront = mCamera->getFront();
		ImGui::Text("Front: (%.2f, %.2f, %.2f)", camFront.x, camFront.y, camFront.z);
		glm::vec3 camUp = mCamera->getUp();
		ImGui::Text("Up: (%.2f, %.2f, %.2f)", camUp.x, camUp.y, camUp.z);
		glm::vec3 camRight = mCamera->getRight();
		ImGui::Text("Right: (%.2f, %.2f, %.2f)", camRight.x, camRight.y, camRight.z);
		ImGui::Text("FOV: %.2f", mCamera->getFOV());
		ImGui::Text("Aspect Ratio: %.2f", mCamera->getAspectRatio());
		ImGui::Text("Near Plane: %.2f", mCamera->getNearPlane());
		ImGui::Text("Far Plane: %.2f", mCamera->getFarPlane());

		glm::mat4 view = mCamera->getViewMatrix();
		glm::mat4 proj = mCamera->getProjectionMatrix();

		if (ImGui::CollapsingHeader("View Matrix"))
		{
			for (int i = 0; i < 4; i++)
			{
				ImGui::Text("%.3f  %.3f  %.3f  %.3f",
					view[i][0], view[i][1], view[i][2], view[i][3]);
			}
		}

		if (ImGui::CollapsingHeader("Projection Matrix"))
		{
			for (int i = 0; i < 4; i++)
			{
				ImGui::Text("%.3f  %.3f  %.3f  %.3f",
					proj[i][0], proj[i][1], proj[i][2], proj[i][3]);
			}
		}
	}
	ImGui::End();
}
#endif