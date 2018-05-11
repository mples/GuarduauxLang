#pragma once

#include <memory>
#include <list>
#include "Statement.h"
#include "FuncDef.h"
#include "Expresion.h"


namespace Guarduaux {
	class FuncCall : public Statement{
	public:
		FuncCall(FuncDef& func_def) : funcDef_(func_def){

		}

		void addParam(std::unique_ptr<Expresion> param){

		}

		unsigned int paramCount(){

		}

		Return run() override{

		}

		FuncDef & getFuncDef() {
			return funcDef_;
		}

	private:

		FuncDef & funcDef_;
		std::list<std::unique_ptr<Expresion> > parameters_;
	};
}