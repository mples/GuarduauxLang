#pragma once

#include <memory>
#include <list>
#include "Statement.h"
#include "Program/FuncDef.h"
#include "Expresions/Expresion.h"


namespace Guarduaux {
	class FuncCall : public Statement{
	public:
		FuncCall(std::shared_ptr<FuncDef> func_def,std::vector<std::unique_ptr<Expresion> > params ) :
				funcDef_(func_def), parameters_(std::move(params)){

		}
		FuncCall( FuncCall & other){
			funcDef_ = other.funcDef_;
			parameters_.swap(other.parameters_);
		}


		Return run() override{
			return funcDef_->run(std::move(parameters_));
		}

		std::shared_ptr<FuncDef> getFuncDef() {
			return funcDef_;
		}

		std::vector<std::unique_ptr<Expresion>> &getParameters_()  {
			return parameters_;
		}

	private:

		std::shared_ptr<FuncDef>  funcDef_;
		std::vector<std::unique_ptr<Expresion> > parameters_;

	};
}