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


        std::shared_ptr<Variable> add(std::shared_ptr<Variable> other);
		std::shared_ptr<Variable> sub(std::shared_ptr<Variable> other);

		std::shared_ptr<Variable> mul(std::shared_ptr<Variable> other);
		std::shared_ptr<Variable> div(std::shared_ptr<Variable> other);

		std::shared_ptr<Variable> equ(std::shared_ptr<Variable> other);
		std::shared_ptr<Variable> neq(std::shared_ptr<Variable> other);

		std::shared_ptr<Variable> negate();

		std::shared_ptr<Variable> lth(std::shared_ptr<Variable> other);
		std::shared_ptr<Variable> loe(std::shared_ptr<Variable> other);
		std::shared_ptr<Variable> gth(std::shared_ptr<Variable> other);
		std::shared_ptr<Variable> goe(std::shared_ptr<Variable> other);

		std::shared_ptr<Variable> and_op(std::shared_ptr<Variable> other);
		std::shared_ptr<Variable> or_op(std::shared_ptr<Variable> other);
		bool isTrue();


        operator bool() const;

		int& get(int i = 0);
		int size();

	private:
		std::vector<int> variableList_;
	};
}


