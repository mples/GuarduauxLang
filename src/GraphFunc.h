#pragma once

#include <vector>
#include <memory>
#include "Statement.h"

namespace Guarduaux {
	class GraphFunc : public Statement {
	public:
		GraphFunc(std::string func_type ) {

		}

		void addParam(std::unique_ptr<Expresion> param){

		}

		Return run() override{

		}

	private:
		std::string funcType_;
		std::list<std::unique_ptr<Expresion> > parameters_;
	};
}