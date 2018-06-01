#pragma once

#include "Variable.h"

namespace Guarduaux {

	struct Return {
		enum Type {
			NONE,
			VARIABLE,
		};

		explicit Return(){
			type_ = Type::NONE;
		}

		explicit Return( std::shared_ptr<Variable> variable){
			type_ = Type::VARIABLE;
			variable_ = variable;
		}

		Type type_;
		std::shared_ptr<Variable> variable_;
	};
}