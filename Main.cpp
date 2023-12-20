#include <glad.h>
#include "include/GLFW/glfw3.h"
#include <vector>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <locale>
#include <codecvt>
#include <iostream>
#include <map>
#include <cctype>
#include <algorithm>


const char* readShaderFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return nullptr;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string shaderSource = buffer.str();

    char* shaderSourcePtr = new char[shaderSource.length() + 1];

    strcpy_s(shaderSourcePtr, shaderSource.length() + 1, shaderSource.c_str());

    return shaderSourcePtr;
}
const bool compileShader(GLuint& shader, GLenum type, const char* source) {
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        return false;
    }
    return true;
}
const bool linkProgram(GLuint& programID, GLuint vertexShader, GLuint fragmentShader) {
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        return false;
    }
    return true;
}

GLuint VAO, VBO, EBO;
GLuint VertexShader, FragmentShader, ShaderProgram;

GLuint VAO2, VBO2, EBO2;
GLuint VertexShader2, FragmentShader2, ShaderProgram2;
float x = 200.0f;
float y = 200.0f;
float height = 160.0f;
float width = 200.0f;
std::vector<float> vectors = {
x, y, 0.0f, 0.0f, 0.0f,
 x + width, y, 0.0f, 1.0f, 0.0f,
 x + width, y + height, 0.0f, 1.0f, 1.0f,
x, y + height, 0.0f, 0.0f, 1.0f
};
std::vector<unsigned int> indices = {
   0, 1, 2,
   2, 3, 0
};

std::vector<float> vectors2 = {
-0.5f, 0.1f, 0.0f, 0.0f, 0.0f,
 0.5f, 0.1f, 0.0f, 1.0f, 0.0f,
 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
-0.5f, -0.5f, 0.0f, 0.0f, 1.0f
};
std::vector<unsigned int> indices2 = {
   0, 1, 2,
   2, 3, 0
};

void PreShader1() {
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* vertexShaderSource = readShaderFile("C:/Users/User/Desktop/Loader/Project1/shader/vertex.vert");
    const char* fragmentShaderSource = readShaderFile("C:/Users/User/Desktop/Loader/Project1/shader/react.frag");

    if (!compileShader(VertexShader, GL_VERTEX_SHADER, vertexShaderSource) ||
        !compileShader(FragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource) ||
        !linkProgram(ShaderProgram, VertexShader, FragmentShader)) {
        std::cerr << "Shader creation failed!" << std::endl;
        ShaderProgram = 0;
    }
    delete vertexShaderSource;
    delete fragmentShaderSource;
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vectors.size(), vectors.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void renderShader1() {

    glUseProgram(ShaderProgram);

    glUniform3f(glGetUniformLocation(ShaderProgram, "color"), 1.0f, 0.0f, 0.0f);
    glUniform2f(glGetUniformLocation(ShaderProgram, "size"), x + width, y + height);


    glm::mat4 projectionMatrix = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    int projectionLoc = glGetUniformLocation(ShaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}
void deleteShader1() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    glDeleteProgram(ShaderProgram);
}
int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
   // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Example", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }
   /*
   Надо Поменять TexCoord на VertexCoord и сделать от 0 до 1 спомощью Resolution 
   Скорей всего дело в том что кординаты маленький тоесть от 0 до 1 лутши сделать спомощью VertexCoord от 0 до 600 и от до 800
   */

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
        glBlendFunc(GL_ALPHA, GL_ALPHA_TEST);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glDepthMask(false);
        glDisable(GL_ALPHA_TEST);
        glShadeModel(7425);

        PreShader1();
        renderShader1();
        deleteShader1();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}