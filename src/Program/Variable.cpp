#include "Variable.h"
#include "Exception.h"

Guarduaux::Variable::Variable() {

}

Guarduaux::Variable::Variable(Guarduaux::Token tok) {

}






Guarduaux::Variable::Variable(int number) {
    variableList_.push_back(number);
}

Guarduaux::Variable::Variable(const std::vector<int>& var_list) {
    variableList_ = var_list;
}

int & Guarduaux::Variable::get(int i ) {
    return variableList_.at(i);
}

int Guarduaux::Variable::size() {
    return variableList_.size();
}

Guarduaux::Variable &Guarduaux::Variable::operator+(const Guarduaux::Variable &other) const {
    Variable var ;
    if(variableList_.size() == other.variableList_.size()){
        var = *this;
        for( int i = 0 ; i < variableList_.size() ; ++i){
            var.variableList_[i] = var.variableList_[i] + other.variableList_[i];
       }
       return var;
    }
    else {
        throw Exception("Cannot add variables size does not match.");
    }
}

Guarduaux::Variable &Guarduaux::Variable::operator-(const Guarduaux::Variable &other) const {
    Variable var ;
    if(variableList_.size() == other.variableList_.size()){
        var = *this;
        for( int i = 0 ; i < variableList_.size() ; ++i){
            var.variableList_[i] = var.variableList_[i] - other.variableList_[i];
        }
        return var;
    }
    else {
        throw Exception("Cannot subtract variables size does not match.");
    }
}

Guarduaux::Variable &Guarduaux::Variable::operator*(const Guarduaux::Variable &other) const {
    Variable var ;
    if(variableList_.size() == other.variableList_.size()){
        var = *this;
        for( int i = 0 ; i < variableList_.size() ; ++i){
            var.variableList_[i] = var.variableList_[i] * other.variableList_[i];
        }
        return var;
    }
    else {
        throw Exception("Cannot multiply variables size does not match.");
    }
}

Guarduaux::Variable &Guarduaux::Variable::operator/(const Guarduaux::Variable &other) const {
    Variable var ;
    if(variableList_.size() == other.variableList_.size()){
        var = *this;
        for( int i = 0 ; i < variableList_.size() ; ++i){
            if(other.variableList_[i] != 0){
                var.variableList_[i] = var.variableList_[i] / other.variableList_[i];
            }
            else{
                throw Exception("Cannot divide by zero.");
            }

        }
        return var;
    }
    else {
        throw Exception("Cannot add variables size does not match.");
    }
}



Guarduaux::Variable &Guarduaux::Variable::operator!() const {
    if( variableList_.empty()){
        Variable var = Variable(1);
        return var;
    }else {
        Variable var = Variable(1);
        return var;
    }
}

Guarduaux::Variable &Guarduaux::Variable::operator==(const Guarduaux::Variable &other) const {
    if(variableList_ == other.variableList_){
        Variable var = Variable(1);
        return var;
    }
    else{
        Variable var = Variable();
        return var;
    }
}

Guarduaux::Variable &Guarduaux::Variable::operator!=(const Guarduaux::Variable &other) const {
    return !(*this == other);
}

Guarduaux::Variable &Guarduaux::Variable::operator<(const Guarduaux::Variable &other) const {
    if(variableList_ < other.variableList_){
        Variable var = Variable(1);
        return var;
    }
    else{
        Variable var = Variable();
        return var;
    }
}

Guarduaux::Variable &Guarduaux::Variable::operator<=(const Guarduaux::Variable &other) const {
    return !(other < *this);
}

Guarduaux::Variable &Guarduaux::Variable::operator>(const Guarduaux::Variable &other) const {
    return other < *this;
}

Guarduaux::Variable &Guarduaux::Variable::operator>=(const Guarduaux::Variable &other) const {
    return !(*this < other);
}

Guarduaux::Variable &Guarduaux::Variable::operator&&(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable::operator bool() const {
    return !variableList_.empty();
}


