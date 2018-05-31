#pragma once

#include "Variable.h"

namespace Guarduaux {

	struct Return {
		enum Type {
			NONE,
			VARIABLE,
			BREAK,
			CONTINUE
		};

		explicit Return(Type type = Type::NONE){
			type = Type::NONE;

		}

		explicit Return(Type type, Variable variable){

		}

		Type type_;
		Variable variable_;
	};
}