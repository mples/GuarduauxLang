#pragma once

#include <string>
#include <list>
#include "Statements/BlockStatement.h"
#include "GraphicContext.h"

namespace Guarduaux {

    using BlockPtr = std::unique_ptr<Guarduaux::BlockStatement>;

	class FuncDef {
	public:

		FuncDef() {}

		FuncDef( std::string &identi,  std::vector<std::string> &param, BlockPtr func) : identifier_(identi),
                                                                                         parameters_(param){
		    funcBlock_ = std::move(func);
		    for(const auto & p : param){
		    	//TODO
				//funcBlock_->addVar(p);
		    }
		}
		FuncDef(const FuncDef&) {

		};
		FuncDef &operator = (const FuncDef&) {

		}
		~FuncDef() = default;


		const std::string& getId() const{
			return identifier_;
		}

		std::shared_ptr<GraphicContext> getGraphicContext_(){
			return funcBlock_->getContext_()->getGraphicContext_();
		}

		unsigned int paramCount(){
			return parameters_.size();
		}

		Return run(std::vector<std::unique_ptr<Expresion> > params){
			std::unordered_map < std::string, std::shared_ptr<Variable> > vars;
			int i = 0;
			for(const auto & param : params){
			    std::string param_name(parameters_[i]);
				vars.insert(std::make_pair< std::string, std::shared_ptr<Variable> >(std::move(param_name), param->calculate() ));
			}
			funcBlock_->updateVars(vars);
            return funcBlock_->run();
		}

		Return run(){
			return funcBlock_->run();

		}

	private:
		const std::string identifier_;
		std::vector<std::string> parameters_;
		BlockPtr funcBlock_;

	};
}