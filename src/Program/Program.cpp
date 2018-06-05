//
// Created by mateusz on 04.06.18.
//

#include "Program.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Graphic/Shader.h>
#include <iostream>

void Guarduaux::Program::addFunc(std::unique_ptr <FuncDef> function) {
    functions.insert({function->getId(), std::move(function)});
}

bool Guarduaux::Program::isVaildFunc(const std::string &func_name) {
    return functions.find(func_name) != functions.end();
}

std::shared_ptr<Guarduaux::FuncDef> Guarduaux::Program::getFuncDef(const std::string &func_name) {
    return functions.at(func_name);
}

Guarduaux::Return Guarduaux::Program::generateScene() {
    auto scene_func = functions.find("scene");
    if(scene_func != functions.end()){
        Return ret = scene_func->second->run();
        graphicContext_ = scene_func->second->getGraphicContext_();
        return ret;
    }
    else {
        throw Exception("No scene function");
    }

}

void Guarduaux::Program::renderScene() {
    for(const auto & ob : graphicContext_->getGraphObjects_()){
        ob.second->draw();
    }

}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Guarduaux::Program::render() {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;


        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return ;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return ;
        }

        Shader ourShader("/home/mateusz/Projects/TKOM/OpenGLTest/source/shader.vert", "/home/mateusz/Projects/TKOM/OpenGLTest/source/shader.frag"); // you can name your shader files however you like
        glEnable(GL_DEPTH_TEST);


        initScene();

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ourShader.use();
            renderScene();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return ;
}

void Guarduaux::Program::initScene() {
    for(const auto & ob : graphicContext_->getGraphObjects_()){
        ob.second->init();
    }
}
