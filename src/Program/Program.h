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

		void addFunc(std::unique_ptr<FuncDef> function);

		bool isVaildFunc(const std::string & func_name);

		std::shared_ptr<FuncDef> getFuncDef(const std::string & func_name);

		Return generateScene();

		void renderScene();

		void initScene();

		void render();

	private:
		std::unordered_map<std::string, std::shared_ptr<FuncDef> > functions;
		std::shared_ptr<GraphicContext> graphicContext_;
	};

}