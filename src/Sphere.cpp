#include "Sphere.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Sphere::Sphere(float radius, int sectors, int stacks, glm::vec3 pos) : position(pos) {
    generateSphere(radius, sectors, stacks);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Sphere::~Sphere() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Sphere::generateSphere(float radius, int sectors, int stacks) {
    float x, y, z, xy; //Vertex coordinates
    float u, v; //Texture coordinates

    float sectorStep = 2 * M_PI / sectors;
    float stackStep = M_PI / stacks;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stacks; i++) {
        stackAngle = M_PI / 2 - i * stackStep; //Starts at pi/2 (North Pole) to -pi/2 (South Pole)
        xy = radius * cosf(stackAngle);  //r * cos(u)
        z = radius * sinf(stackAngle);   //r * sin(u)

        for (int j = 0; j <= sectors; j++) {
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);  //r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);  //r * cos(u) * sin(v)

            //Add to vector(X, Y, Z)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            //Coordinates UV for textures
            u = (float)j / sectors;
            v = (float)i / stacks;

            vertices.push_back(u);
            vertices.push_back(v);
        }
    }

    int k1, k2;

    for (int i = 0; i < stacks; i++) {
        k1 = i * (sectors + 1); //beginning of current stack
        k2 = k1 + sectors + 1;  //beginning of next stack

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            //k1 => k2 => k1 + 1
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            // k1 + 1 => k2 => k2 + 1
            if (i != (stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
        indexCount = indices.size();
    }
}

void Sphere::draw(const Shader &shader) const{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}