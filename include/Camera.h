#ifndef SHOOTER_CAMERA_H
#define SHOOTER_CAMERA_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

enum cameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:

    glm::vec3 position{};
    glm::vec3 front;
    glm::vec3 right{};
    glm::vec3 worldUp{};
    glm::vec3 up{};

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    //Constructor
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    glm::mat4 GetViewMatrix() const;

    void ProcessKeyboard(cameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
    void ProcessMouseScroll(float yoffset);

private:

    void updateCameraVectors();
};
#endif //SHOOTER_CAMERA_H
