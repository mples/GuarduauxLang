#pragma once

#include <memory>
#include <utility>
#include <functional>

#include "Lexer/Lexer.h"
#include "Program/Program.h"
#include "Statements/Statement.h"
#include "Program/Context.h"




namespace Guarduaux {

	using StatemPtr = std::unique_ptr<Statement>;
	using ExprPtr = std::unique_ptr<Expresion>;
    using BlockPtr = std::unique_ptr<Guarduaux::BlockStatement>;
	using Type = TokenType;

	class Parser
	{
	public:
		Parser() = default;

		Parser(std::unique_ptr<Lexer> lexer);

		void setLexer(std::unique_ptr<Lexer> lexer);

		void clearLexer();

		~Parser() = default;

		Program & parse();

	private:
		std::unique_ptr<Lexer> lexer_;

		Program prog_;

		Context* currContext_ = nullptr;

		void parseProgram();

		bool isAcceptable(Type type, std::function<void()> func = std::function<void()>());

		void isAcceptableOrThrow(Type type, std::function<void()> func = std::function<void()>());

        std::unique_ptr<FuncDef> funcDefParse();
		std::vector<std::string> parametersParse();
		BlockPtr blockStateParse();

		StatemPtr funcCallOrAssinStatemOrInitStatemParse(Token token);
		StatemPtr ifStatemParse();
		StatemPtr funcCallParse(Token token);
		StatemPtr perioFuncCallParse(Token token, StatemPtr func_call);
		StatemPtr loopStatemParse(Token loop_token);

		StatemPtr assignOrGraphicStatemParse(Token token);
		StatemPtr assignStatemParse(Token token, ExprPtr index);
		StatemPtr graphicStatemParse(Token token, Token var_name, ExprPtr index);
		StatemPtr drawFuncParse(Token var_name, ExprPtr index);
		StatemPtr scaleFuncParse(Token var_name, ExprPtr index);
		StatemPtr moveFuncParse(Token var_name, ExprPtr index);
		StatemPtr chngcolFuncParse(Token var_name, ExprPtr index);
		StatemPtr otherGrpahFunParse(Token token,Token var_name, ExprPtr index);
		StatemPtr returnStatemParse();


		ExprPtr logicExprParse();
		ExprPtr andExprParse();
		ExprPtr relatExprParse();
		ExprPtr simplLogicExprParse();

		ExprPtr assignableExprParse();
		ExprPtr simplAssnbleExprParse();
		ExprPtr multpExprParse();

		std::unique_ptr<Variable> numberParse();
	};


}
