#pragma once

#include "Program/Variable.h"

namespace Guarduaux {
	
	//class Variable;

	class Expresion {
	public:
		virtual ~Expresion() = default;

		virtual Variable calculate()  = 0;
	};
}