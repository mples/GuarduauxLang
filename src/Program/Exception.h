#pragma once

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <list>

#include "Token/Token.h"
#include "Token/TokenTypeTable.h"

namespace Guarduaux {
	class Exception : std::runtime_error {
	public:
		Exception() : runtime_error("Error") {
			std::cout << "Error" << std::endl;
		}
		Exception(const std::string& err_msg) : runtime_error(err_msg) {
			std::cout << err_msg << std::endl;
		}
	};

	class WrongTokenException : Exception {
	public:
		WrongTokenException(const Token &token, std::list<TokenType> tokens)  {
			std::string exp_tokens;
			exp_tokens.append("Wrong token: " + token.value_ + ". Expected token types: ");
			for (auto &&t : tokens) {
				exp_tokens.append(TokenTypeTable::getName(t));
				exp_tokens.append(" ");
			}
			exp_tokens += " at line " + token.getPos().toString();
			Exception(std::string(exp_tokens));
			
		}
	};



}
