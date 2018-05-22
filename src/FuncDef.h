#pragma once

#include <string>
#include <list>
#include "BlockStatement.h"

namespace Guarduaux {

    using BlockPtr = std::unique_ptr<Guarduaux::BlockStatement>;

	class FuncDef {
	public:

		FuncDef() {}



		FuncDef( std::string &identi,  std::vector<std::string> &param, BlockPtr func)
				 {}

		void addParameter(const std::string &identifier){

		}

		std::string& getIdentif() const{

		}



		unsigned int paramCount(){

		}

		Return run(){

		}
	private:
		std::string identifier_;
		std::vector<std::string> parameters_;
		BlockPtr funcBlock_;

	};
}