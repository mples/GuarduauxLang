#pragma once

#include <vector>
#include <memory>
#include "Token/Token.h"


namespace Guarduaux {

	//class Expresion;

	class Variable
	{
	public:
		Variable();
		Variable(Token tok);
		Variable(int number);

		Variable(std::vector<int> var_list);

		Variable& operator=(const Variable& other);

        Variable& operator*(const Variable &other) const;
        Variable& operator/(const Variable &other) const;

        Variable& operator+(const Variable &other) const;
        Variable& operator-(const Variable &other) const;

        Variable& operator!() const;

        Variable& operator==(const Variable &other) const;
        Variable& operator!=(const Variable &other) const;

        Variable& operator<(const Variable &other) const;
        Variable& operator<=(const Variable &other) const;
        Variable& operator>(const Variable &other) const;
        Variable& operator>=(const Variable &other) const;

        Variable& operator&&(const Variable &other) const;

		Variable get(int i = 0);
		int calculate();

	private:
		std::vector<int> variableList_;
	};
}


