#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Sphere.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    constexpr int resx = 1440;
    constexpr int resy = 1080;

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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        myShader.useShader();

        glm::mat4 view = glm::mat4(1.0f);
        // Alejar la cámara 5 unidades hacia atrás para poder ver la esfera
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)resx / (float)resy, 0.1f, 100.0f);

        myShader.setMat4("view", view);
        myShader.setMat4("projection", projection);

        myShader.setVec4("ourColor", 0.8f, 0.3f, 0.0f, 1.0f);
        mySphere.draw(myShader);

        glfwSwapBuffers(window);
        glfwPollEvents(); //this function checks if any event is triggered
    }


    glfwTerminate();
    return 0;
}