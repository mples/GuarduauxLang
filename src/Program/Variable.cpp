#include "Variable.h"


Guarduaux::Variable::Variable() {

}

Guarduaux::Variable::Variable(Guarduaux::Token tok) {

}


Guarduaux::Variable &Guarduaux::Variable::operator=(const Guarduaux::Variable &other) {
}



Guarduaux::Variable::Variable(int number) {
    variableList_.push_back(number);
}

Guarduaux::Variable::Variable(std::vector<int> var_list) {

}

Guarduaux::Variable Guarduaux::Variable::get(int i ) {
    return variableList_.at(i);
}

int Guarduaux::Variable::calculate() {
    return 0;
}

Guarduaux::Variable &Guarduaux::Variable::operator*(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator/(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator+(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator-(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator!() const {

}

Guarduaux::Variable &Guarduaux::Variable::operator==(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator!=(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator<(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator<=(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator>(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator>=(const Guarduaux::Variable &other) const {

}

Guarduaux::Variable &Guarduaux::Variable::operator&&(const Guarduaux::Variable &other) const {

}

