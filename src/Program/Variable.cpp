#include "Variable.h"
#include "Exception.h"

Guarduaux::Variable::Variable() {

}

Guarduaux::Variable::Variable(Guarduaux::Token tok) {

}
Guarduaux::Variable::Variable(int number, int size) {
    variableList_.resize(size);
    variableList_.push_back(number);
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

Guarduaux::Variable::operator bool() const {
    return !variableList_.empty();
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::add(std::shared_ptr<Guarduaux::Variable> other) {
    Variable var ;
    if(variableList_.size() == other->variableList_.size()){
        var = *this;
        for( int i = 0 ; i < variableList_.size() ; ++i){
            var.variableList_[i] = var.variableList_[i] + other->variableList_[i];
        }
        return std::make_shared<Variable>(var);
    }
    else {
        throw Exception("Cannot add variables size does not match.");
    }
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::sub(std::shared_ptr<Guarduaux::Variable> other) {
    Variable var ;
    if(variableList_.size() == other->variableList_.size()){
        var = *this;
        for( int i = 0 ; i < variableList_.size() ; ++i){
            var.variableList_[i] = var.variableList_[i] - other->variableList_[i];
        }
        return std::make_shared<Variable>(var);
    }
    else {
        throw Exception("Cannot add variables size does not match.");
    }
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::mul(std::shared_ptr<Guarduaux::Variable> other) {
    Variable var ;
    if(variableList_.size() == other->variableList_.size()){
        var = *this;
        for( int i = 0 ; i < variableList_.size() ; ++i){
            var.variableList_[i] = var.variableList_[i] * other->variableList_[i];
        }
        return std::make_shared<Variable>(var);
    }
    else {
        throw Exception("Cannot add variables size does not match.");
    }
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::div(std::shared_ptr<Guarduaux::Variable> other) {
    Variable var ;
    if(variableList_.size() == other->variableList_.size()){
        var = *this;
        for( int i = 0 ; i < variableList_.size() ; ++i){
            if(other->variableList_[i] != 0){
                var.variableList_[i] = var.variableList_[i] / other->variableList_[i];
            }
            else {
                throw Exception("Cannot divide by zero.");
            }
        }
        return std::make_shared<Variable>(var);
    }
    else {
        throw Exception("Cannot add variables size does not match.");
    }
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::equ(std::shared_ptr<Guarduaux::Variable> other) {
    if(variableList_ == other->variableList_){
        Variable var = Variable(1);
        return std::make_shared<Variable>(var);;
    }
    else{
        Variable var = Variable(0);
        return std::make_shared<Variable>(var);
    }
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::neq(std::shared_ptr<Guarduaux::Variable> other) {
    auto var = std::make_shared<Variable>(*this);
    return  (var->equ( other) )->negate() ;
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::negate() {
    Variable var;
    if( !variableList_.empty()){
        if(variableList_.at(0) == 1){
            var = Variable(0);
        }
        else {
            var = Variable(1);
        }
    }else {
        var = Variable(0);
    }
    return std::make_shared<Variable>(var);
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::lth(std::shared_ptr<Guarduaux::Variable> other) {
    if(variableList_ < other->variableList_){
        Variable var = Variable(1);
        return std::make_shared<Variable>(var);
    }
    else{
        Variable var = Variable(0);
        return std::make_shared<Variable>(var);
    }
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::loe(std::shared_ptr<Guarduaux::Variable> other) {
    auto var = std::make_shared<Variable>(*this);
    return (other->lth(var))->negate();
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::gth(std::shared_ptr<Guarduaux::Variable> other) {
    auto var = std::make_shared<Variable>(*this);
    return other->lth(var);
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::goe(std::shared_ptr<Guarduaux::Variable> other) {
    auto var = std::make_shared<Variable>(*this);
    return (var->lth(other))->negate();
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::and_op(std::shared_ptr<Guarduaux::Variable> other) {
    if(other->isTrue() && isTrue() ){
        Variable var = Variable(1);
        return std::make_shared<Variable>(var);
    }
    else {
        Variable var = Variable(0);
        return std::make_shared<Variable>(var);
    }
}

std::shared_ptr<Guarduaux::Variable> Guarduaux::Variable::or_op(std::shared_ptr<Guarduaux::Variable> other) {
    if(other->isTrue() || isTrue() ){
        Variable var = Variable(1);
        return std::make_shared<Variable>(var);
    }
    else {
        Variable var = Variable(0);
        return std::make_shared<Variable>(var);
    }
}

bool Guarduaux::Variable::isTrue() {
    if(!variableList_.empty()){
        if(variableList_.at(0) == 0){
            return false;
        }
        else
            return true;
    }else
        return false;

}

void Guarduaux::Variable::resize(int size) {
    variableList_.resize(size);
}




