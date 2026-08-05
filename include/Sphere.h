#ifndef SHOOTER_SPHERE_H
#define SHOOTER_SPHERE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"

class Sphere {
public:
    glm::vec3 position;

    Sphere(float radius, int sectors, int stacks, glm::vec3 pos);
    ~Sphere();

    void draw(const Shader &shader) const;

private:
    unsigned int VAO, VBO, EBO;
    int indexCount;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void generateSphere(float radius, int sectors, int stacks);
};
#endif //SHOOTER_SPHERE_H
