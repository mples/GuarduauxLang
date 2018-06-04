#pragma once

#include "Variable.h"
#include "Graphic/GraphicObject.h"
namespace Guarduaux {

	struct Return {
		enum Type {
			NONE,
			VARIABLE,
			OBJECT
		};

		explicit Return(){
			type_ = Type::NONE;
		}

		explicit Return( std::shared_ptr<Variable> variable){
			type_ = Type::VARIABLE;
			variable_ = variable;
		}

		explicit Return( std::string obj_name, std::shared_ptr<GraphicObject> object){
			type_ = Type::OBJECT;
			objName = std::move(obj_name);
			object_ = std::move(object);
		}


		Type type_;
		std::shared_ptr<Variable> variable_;
		std::shared_ptr<GraphicObject> object_;
		std::string objName;
	};
}