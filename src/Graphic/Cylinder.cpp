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

    std::cout << dim_[0] << dim_[1] << dim_[2] << std::endl;
    std::cout << col_[0] << col_[1] << col_[2] << std::endl;
    std::cout << pos_[0] << pos_[1] << pos_[2] << std::endl;
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
