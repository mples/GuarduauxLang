#pragma once
#include "Input.h"
#include "Token.h"

namespace Guarduaux {

	static int IDENTIFIER_MAX_LENGTH = 64;
	class Lexer
	{
	public:
		Lexer(Input inp);
		~Lexer();

		Token getToken();
		Token currentToken() const;

	private:
		Input input_;
		char lastch_;
		std::string buffer_;
		Position pos_;
		Token currentToken_;

		void ignoreWhiteSpace();
		void processNextChar();
		void cacheNextChar();


		Token tryIdentifier();
		Token tryKeyword();

		Token tryFunc();
		Token tryReturn();
		Token tryIf();
		Token tryElse();
		Token tryFor();
		Token tryForEach();
		Token tryDraw();
		Token tryScale();
		Token tryMove();
		Token tryChngCol();
		Token tryDim();
		Token tryPos();
		Token tryCol();
		Token tryBox();
		Token trySphere();

		Token tryNumber();
		Token tryOperator();

		Token tryPeriodicalOp();
		Token tryEqualOp();
		Token tryMultiOp();
		Token tryAddtvOp();
		Token tryRelatOp();
		Token tryLogicOp();

		Token trySpecialSign();

	};
}




