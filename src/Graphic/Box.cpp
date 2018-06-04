//
// Created by mateusz on 04.06.18.
//

#include "Box.h"
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static GLfloat boxMesh[] = {

        //front
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        //back
        -0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f,  -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,

        //right
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f,  -0.5f, -0.5f,
        0.5f,  0.5f, 0.5f,
        0.5f,  -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        //left
        -0.5f, 0.5f, 0.5f,
        -0.5f,  -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f,  -0.5f, -0.5f,

        //up
        0.5f, 0.5f, 0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

        //down
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f,  -0.5f, -0.5f,
        0.5f,  -0.5f, 0.5f,
        -0.5f,  -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,

};

void Guarduaux::Box::draw() {

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}

Guarduaux::Box::Box(std::vector<int> pos, std::vector<int> col, std::vector<int> dim) {
    dim_ = std::move(dim);
    pos_ = std::move(pos);
    col_ = std::move(col);
}

void Guarduaux::Box::move(std::vector<int> vec) {
    if(pos_.size() == vec.size() == 3){
        for(int i = 0 ; i < pos_.size() ; ++i ) {
            pos_[i] += vec[i];
        }
    }

}

void Guarduaux::Box::scale(std::vector<int> vec) {
    if(dim_.size() == vec.size() == 3){
        for(int i = 0 ; i < dim_.size() ; ++i ) {
            dim_[i] *= vec[i];
        }
    }
}

void Guarduaux::Box::chngcol(std::vector<int> vec) {
    if(col_.size() == vec.size() == 3){
        for(int i = 0 ; i < col_.size() ; ++i ) {
            col_[i] = vec[i];
        }
    }
}

void Guarduaux::Box::init() {

    initBoxCoord();
    if( !boxCoord.empty()){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * boxCoord.size(), &(boxCoord[0]), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

}

void Guarduaux::Box::initBoxCoord() {

    glm::vec3 pos_float(pos_[0]/100.f, pos_[1]/100.f, pos_[2]/100.f);

    glm::vec3 col_float((col_[0]/100.f), (col_[1]/100.f), col_[2]/100.f);

    glm::vec3 dim_float(dim_[0]/100.f, dim_[1]/100.f, dim_[2]/100.f);

    for (int i = 0; i < (36) ; ++i) {
        glm::vec3 poss(((boxMesh[i * 3]  * dim_float.x) + pos_float.x),
                       ((boxMesh[i * 3 + 1]  * dim_float.y) + pos_float.y) ,
                       ((boxMesh[i * 3 + 2]  * dim_float.z) + pos_float.z ) );



        boxCoord.push_back(poss.x) ;
        boxCoord.push_back(poss.y);
        boxCoord.push_back(poss.z);
        boxCoord.push_back(col_float.x);
        boxCoord.push_back(col_float.y ) ;
        boxCoord.push_back(col_float.z);
    }
}
