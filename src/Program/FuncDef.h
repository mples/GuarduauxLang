#pragma once

#include <string>
#include <list>
#include "Statements/BlockStatement.h"

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



		unsigned int paramCount(){
			return parameters_.size();
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