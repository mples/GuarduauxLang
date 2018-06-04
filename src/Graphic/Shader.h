//
// Created by mateusz on 04.06.18.
//

#ifndef GUARDUAUX_LANG_SHADER_H
#define GUARDUAUX_LANG_SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Guarduaux {
    class Shader
    {
    public:
        unsigned int ID;

        unsigned int getID() const;

        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        void use();
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;

    };

}




#endif //GUARDUAUX_LANG_SHADER_H
