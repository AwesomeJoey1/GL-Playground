#include "Cube.h"

// Axis aligned plane (xy plane)
Cube::Cube()
{
    float halfWidth = 0.5f;
    float vertices[24 * 3] = {
        // Front
       -halfWidth, -halfWidth, halfWidth,
        halfWidth, -halfWidth, halfWidth,
        halfWidth,  halfWidth, halfWidth,
       -halfWidth,  halfWidth, halfWidth,
       // Right
        halfWidth, -halfWidth, halfWidth,
        halfWidth, -halfWidth, -halfWidth,
        halfWidth,  halfWidth, -halfWidth,
        halfWidth,  halfWidth, halfWidth,
        // Back
        -halfWidth, -halfWidth, -halfWidth,
        -halfWidth,  halfWidth, -halfWidth,
         halfWidth,  halfWidth, -halfWidth,
         halfWidth, -halfWidth, -halfWidth,
         // Left
         -halfWidth, -halfWidth, halfWidth,
         -halfWidth,  halfWidth, halfWidth,
         -halfWidth,  halfWidth, -halfWidth,
         -halfWidth, -halfWidth, -halfWidth,
         // Bottom
         -halfWidth, -halfWidth, halfWidth,
         -halfWidth, -halfWidth, -halfWidth,
          halfWidth, -halfWidth, -halfWidth,
          halfWidth, -halfWidth, halfWidth,
          // Top
          -halfWidth,  halfWidth, halfWidth,
           halfWidth,  halfWidth, halfWidth,
           halfWidth,  halfWidth, -halfWidth,
          -halfWidth,  halfWidth, -halfWidth
    };

    float normals[24 * 3] = {
        // Front
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // Right
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // Back
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        // Left
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        // Bottom
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        // Top
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    float textureCoords[24 * 2] = {
        // Front
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Right
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Back
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Left
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Bottom
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Top
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    GLuint indices[] = {
        0,1,2,0,2,3,
        4,5,6,4,6,7,
        8,9,10,8,10,11,
        12,13,14,12,14,15,
        16,17,18,16,18,19,
        20,21,22,20,22,23
    };

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    unsigned int bufferHandles[4];
    glGenBuffers(4, bufferHandles);
    glBindBuffer(GL_ARRAY_BUFFER, bufferHandles[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, bufferHandles[1]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, bufferHandles[2]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 2 * sizeof(float), textureCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferHandles[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}


void Cube::render()
{
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}
