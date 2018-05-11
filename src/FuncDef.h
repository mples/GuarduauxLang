#pragma once

#include <string>
#include <list>
#include "BlockStatement.h"

namespace Guarduaux {
	class FuncDef {
	public:

		FuncDef() {

		}

		FuncDef(std::string func_name) : identifier_(func_name) {

		}

		void addParameter(const std::string &identifier){

		}

		std::string& getIdentif() const{

		}

		BlockStatement& getFuncBlock(){

		}

		unsigned int paramCount(){

		}

		Return run(){

		}
	private:
		const std::string identifier_;
		std::list<std::string> parameters_;
		BlockStatement funcBlock_;

	};
}