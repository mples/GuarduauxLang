#pragma once
#include "Input.h"
#include "Token/Token.h"

namespace Guarduaux {

	static int IDENTIFIER_MAX_LENGTH = 64;
	class Lexer
	{
	public:
		Lexer(Input inp);
		~Lexer();

		Token & getToken();
		Token & currentToken();

	private:
		Input input_;
		char lastch_;
		std::string buffer_;
		Position pos_;
		Token currentToken_;

		void ignoreWhiteSpace();
		void processNextChar();
		void cacheNextChar();


		void tryIdentifier();
		void tryKeyword();

		void tryNumber();
		void tryOperator();

		void tryPeriodicalOp();
		void tryEqualOp();

        void tryMultiOp();

        void tryAddtvOp();

        void tryRelatOp();

        void tryLogicOp();

        void trySpecialSign();

	};
}




