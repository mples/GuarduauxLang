//
// Created by mateusz on 04.06.18.
//

#include "Cylinder.h"
#include <iostream>

Guarduaux::Cylinder::Cylinder(std::vector<int> pos, std::vector<int> col, std::vector<int> dim) {
    dim_ = std::move(dim);
    pos_ = std::move(pos);
    col_ = std::move(col);
}

void Guarduaux::Cylinder::draw() {
    std::cout << "draw cylinder" << std::endl;
}

void Guarduaux::Cylinder::move(std::vector<int> vec) {
    if(pos_.size() == vec.size() == 3){
        for(int i = 0 ; i < pos_.size() ; ++i ) {
            pos_[i] += vec[i];
        }
    }
}

void Guarduaux::Cylinder::scale(std::vector<int> vec) {
    if(dim_.size() == vec.size() == 3){
        for(int i = 0 ; i < dim_.size() ; ++i ) {
            dim_[i] *= vec[i];
        }
    }
}

void Guarduaux::Cylinder::chngcol(std::vector<int> vec) {
    if(col_.size() == vec.size() == 3){
        for(int i = 0 ; i < col_.size() ; ++i ) {
            col_[i] = vec[i];
        }
    }
}

void Guarduaux::Cylinder::init() {
    initCylinCoord();
    if( !cylinCoord_.empty()){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * cylinCoord_.size(), &(cylinCoord_[0]), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

void Guarduaux::Cylinder::initCylinCoord() {

    glm::vec3 pos_float(pos_[0]/100.f, pos_[1]/100.f, pos_[2]/100.f);

    glm::vec3 col_float((col_[0]/100.f), (col_[1]/100.f), col_[2]/100.f);

    glm::vec3 dim_float(dim_[0]/100.f, dim_[1]/100.f, dim_[2]/100.f);


}
