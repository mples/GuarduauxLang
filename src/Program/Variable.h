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

		Variable(const Variable&) = default;

		Variable(const std::vector<int> &var_list);

		//Variable& operator=(const Variable& other);

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
        operator bool() const;

		int& get(int i = 0);
		int size();

	private:
		std::vector<int> variableList_;
	};
}


