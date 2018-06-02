#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <itclInt.h>
#include "FuncDef.h"
#include "Exception.h"

namespace Guarduaux {

	class Program {
	public:
		Program() = default;

		void addFunc(std::unique_ptr<FuncDef> function){
			functions.insert({function->getId(), std::move(function)});
		}

		bool isVaildFunc(const std::string & func_name){
			return functions.find(func_name) != functions.end();
		}

		std::shared_ptr<FuncDef> getFuncDef(const std::string & func_name) {
			return functions.at(func_name);
		}

		Return run(){
			auto scene_func = functions.find("scene");
			if(scene_func != functions.end()){
				return scene_func->second->run();
			}
			else {
				throw Exception("No scene function");
			}

		}

	private:
		std::unordered_map<std::string, std::shared_ptr<FuncDef> > functions;
	};

}