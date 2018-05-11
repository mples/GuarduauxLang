#pragma once

#include <vector>
#include "Token.h"



namespace Guarduaux {

	//class Expresion;

	class Variable
	{
	public:
		Variable();
		Variable(Token tok);
		Variable(std::vector<Variable> var_list);

		//TODO
	private:
		std::vector<Variable> variableList_;
	};
}


