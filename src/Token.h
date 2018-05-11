#pragma once

//#include <ostream>
//#include <string>
#include "TokenType.h"

namespace Guarduaux {
	struct Position {
		Position(int l = 0, int c = 0) : line_(l), column_(c) {
		}

		int line_;
		int column_;
	};

	struct Token {
		TokenType type_;

		std::string value_;
		Position pos_;


		Token(TokenType type, std::string s = "") : type_(type), value_(s) {

		}

		void setPos(const Position& p) {
			pos_ = p;
		}
		void setPos(int line, int column) {
			pos_.line_ = line;
			pos_.column_ = column;
		}
		std::string getPos() const {
			std::string pos_str;
			pos_str += "line: ";
			pos_str += pos_.line_;
			pos_str += " column: ";
			pos_str += pos_.column_;
			return pos_str;
		}

		bool isVaild() const {
			return type_ != TokenType::UNIDENTIFIED;
		}
		static Token unidentifiedType() {
			return Token(TokenType::UNIDENTIFIED);
		}

	};

}

