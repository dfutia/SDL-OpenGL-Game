#include "renderer/camerabehavior.h"
#include "renderer/camera.h"
#include "core/input.h"
#include "core/services.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void DebugCamera::Update(Camera& camera, double deltaTime)
{
    static Input* input = Services::getService<Input>("Input");

    float speed = 5.0f * static_cast<float>(deltaTime);
    float mouseSensitivity = 0.1f;
    static float yaw = -90.0f, pitch = 0.0f;

    glm::vec3 position = camera.getPosition();
    glm::vec3 front = camera.getFront();
    glm::vec3 up = camera.getUp();
    glm::vec3 right = glm::normalize(glm::cross(front, up));

    if (input->getKeyboard()->isKeyDown(Key::W))
        position += front * speed;
    if (input->getKeyboard()->isKeyDown(Key::S))
        position -= front * speed;
    if (input->getKeyboard()->isKeyDown(Key::A))
        position -= right * speed;
    if (input->getKeyboard()->isKeyDown(Key::D))
        position += right * speed;
    camera.setPosition(position);

    if (input->getMouse()->isButtonPressed(MouseButton::Right)) {
        input->getMouse()->setCursorMode(CursorMode::Locked); 
    }
    else if (input->getMouse()->isButtonReleased(MouseButton::Right)) {
        input->getMouse()->setCursorMode(CursorMode::Normal);
    }

    if (input->getMouse()->isButtonDown(MouseButton::Right)) {
		glm::vec2 mouseDelta = input->getMouse()->getMouseDelta();
        yaw += mouseDelta.x * mouseSensitivity;
        pitch -= mouseDelta.y * mouseSensitivity;
        pitch = glm::clamp(pitch, -89.0f, 89.0f);

        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront = glm::normalize(newFront);

        glm::vec3 newRight = glm::normalize(glm::cross(newFront, glm::vec3(0, 1, 0)));
        glm::vec3 newUp = glm::normalize(glm::cross(newRight, newFront));

        camera.setFront(newFront);
        camera.setRight(newRight);
        camera.setUp(newUp);
    }
}