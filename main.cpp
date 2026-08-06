#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Sphere.h"
#include "Camera.h"

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

constexpr int resx = 1440;
constexpr int resy = 1080;

float lastX = resx / 2.0f;
float lastY = resy / 2.0f;
bool firstMouse = true;

//Delta Time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


int main() {

    //Initialize GLFW
    if (!glfwInit ()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //requirement for macOs

    GLFWwindow* window = glfwCreateWindow(resx, resy, "Shooter", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "[ERROR]: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Initialize GLAD to manage function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "[ERROR]: Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader myShader("shaders/basico.vert", "shaders/basico.frag");
    Sphere mySphere(1.0f, 72, 36, glm::vec3(0.0f, 0.0f, 0.0f));

    //Active Z-BUFFER
    glEnable(GL_DEPTH_TEST);

    //GameLoop
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        myShader.useShader();

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)resx / (float)resy, 0.1f, 100.0f);

        myShader.setMat4("projection", projection);
        myShader.setMat4("view", view);

        myShader.setVec4("ourColor", 0.8f, 0.3f, 0.0f, 1.0f);
        mySphere.draw(myShader);

        glfwSwapBuffers(window);
        glfwPollEvents(); //this function checks if any event is triggered
    }


    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //We send the deltaTime to the camera to ensure the movement speed is stable
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    //Avoid a sudden camera jump the first time the mouse enters the window
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; //Inverted in OpenGL, the Y-axis goes from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}