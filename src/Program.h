#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "FuncDef.h"

namespace Guarduaux {

	class Program {
	public:
		Program() = default;

		void addFunc(std::unique_ptr<FuncDef> function){

		}

		bool isVaildFunc(const std::string fun_name){

		}

		FuncDef& getFuncDef(const std::string fun_name) {
			return *functions.at(fun_name);
		}

		Return run(){

		}

	private:
		std::unordered_map<std::string, std::unique_ptr<FuncDef> > functions;
	};

}