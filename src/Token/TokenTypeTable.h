#pragma once

#include <unordered_map>
#include <string>

#include "TokenType.h"

namespace Guarduaux {

	struct TokenTypeTable
	{
	public:
		static const std::string getName(const TokenType& type);
	private:
		
	};

}

