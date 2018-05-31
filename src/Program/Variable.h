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
		Variable(const Variable & other);
		Variable(Token tok);
		Variable(int number);
		Variable(std::vector<Variable> var_list);

		Variable& operator=(const Variable& other);

		//TODO
	private:
		std::vector<Variable> variableList_;
	};
}


