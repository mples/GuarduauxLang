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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Guarduaux::Program::render() {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return ;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return ;
        }

        Shader ourShader("/home/mateusz/Projects/TKOM/OpenGLTest/source/shader.vert", "/home/mateusz/Projects/TKOM/OpenGLTest/source/shader.frag"); // you can name your shader files however you like
        glEnable(GL_DEPTH_TEST);


        initScene();



        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        // glBindVertexArray(0);


        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            processInput(window);


            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // render the triangle
            ourShader.use();
            renderScene();

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------


        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return ;
}

void Guarduaux::Program::initScene() {
    for(const auto & ob : graphicContext_->getGraphObjects_()){
        ob.second->init();
    }
}
