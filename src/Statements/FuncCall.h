#pragma once

#include <memory>
#include <list>
#include "Statement.h"
#include "Program/FuncDef.h"
#include "Expresions/Expresion.h"


namespace Guarduaux {
	class FuncCall : public Statement{
	public:
		FuncCall(FuncDef& func_def,std::vector<std::unique_ptr<Expresion> > params ) :
				funcDef_(func_def), parameters_(std::move(params)){

		}
		FuncCall( FuncCall & other){
			funcDef_ = other.funcDef_;
			parameters_.swap(other.parameters_);
		}


		Return run() override{
			//TODO add parametes to duncdef run
			return funcDef_.run();
		}

		FuncDef & getFuncDef() {
			return funcDef_;
		}

		std::vector<std::unique_ptr<Expresion>> &getParameters_()  {
			return parameters_;
		}

	private:

		FuncDef  funcDef_;
		std::vector<std::unique_ptr<Expresion> > parameters_;

	};
}