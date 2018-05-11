#pragma once

#include <memory>
#include <utility>
#include <functional>

#include "Lexer.h"
#include "Program.h"
#include "Statement.h"




namespace Guarduaux {

	using StatemPtr = std::unique_ptr<Statement>;
	using ExprPtr = std::unique_ptr<Expresion>;
	using Type = TokenType;

	class Parser
	{
	public:
		Parser() = default;

		Parser(std::unique_ptr<Lexer> lexer);

		void setLexer(std::unique_ptr<Lexer> lexer);

		void clearLexer();

		~Parser() = default;

		void parse();

	private:
		std::unique_ptr<Lexer> lexer_;

		Program prog_;

		BlockStatement* block_;

		void parseProgram();

		bool isAcceptable(Type type, std::function<void()> func = std::function<void()>());

		void isAcceptableOrThrow(Type type, std::function<void()> func = std::function<void()>());

		void funcDefParse();
		void parametersParse(FuncDef& func);
		void blockStateParse(BlockStatement& block);

		StatemPtr funcCallOrAssinStatemOrInitStatemParse(Token token);
		StatemPtr ifStatemParse();
		StatemPtr funcCallParse(Token token);
		StatemPtr perioFuncCallParse(Token token, StatemPtr func_call);
		StatemPtr loopStatemParse();

		StatemPtr assignOrGraphicStatemParse(Token token);
		StatemPtr assignStatemParse(Token token, ExprPtr index);
		StatemPtr graphicStatemParse(Token token, ExprPtr index);
		StatemPtr drawFuncParse(Token token, ExprPtr index);
		StatemPtr otherGrpahFunParse(Token token, ExprPtr index);


		ExprPtr logicExprParse();
		ExprPtr andExprParse();
		ExprPtr relatExprParse();
		ExprPtr simplLogicExprParse();

		ExprPtr assignableExprParse();
		ExprPtr multpExprParse();
	};


}
