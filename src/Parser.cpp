#include "Parser.h"

#include <memory>
#include <unordered_map>
#include <list>
#include <functional>

#include <Program.h>
#include "Expresion.h"
#include "Exception.h"
#include "Variable.h"
#include "FuncCall.h"
#include "FuncDef.h"
#include "IfStatement.h"
#include "AssignStatement.h"
#include "ForStatement.h"
#include "ForEachStatement.h"
#include "PeriodicFuncCall.h"
#include "LogicExpression.h"
#include "AddExpression.h"
#include "RelatExpression.h"
#include "SimpleLogicExpression.h"
#include "AssignableExpression.h"
#include "SimpleAssnblExpression.h"
#include "MultipExpression.h"
#include "GraphFunc.h"

using namespace Guarduaux;

using Type = Guarduaux::TokenType;
using StatemPtr = std::unique_ptr<Guarduaux::Statement>;
using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using BlockPtr = std::unique_ptr<Guarduaux::BlockStatement>;
using AssignPtr = std::unique_ptr<Guarduaux::AssignStatement>;



Parser::Parser(std::unique_ptr<Lexer> lexer) : lexer_(std::move(lexer) ) 
{
}

void Parser::setLexer(std::unique_ptr<Lexer> lexer)
{
	lexer_ = std::move(lexer);
}

void Parser::clearLexer()
{
	lexer_.reset(nullptr);
}

void Parser::parse()
{
	if (lexer_) {
		lexer_->getToken();
		parseProgram();
	}
}

void Parser::parseProgram()
{
	while (lexer_->currentToken().type_ != Type::END_OF_FILE  ) {

		if (isAcceptable(Type::FUNC)) {
			funcDefParse();
		}
		else {
			throw WrongTokenException(lexer_->currentToken(), { TokenType::FUNC, TokenType::END_OF_FILE });
		}
	}
}

bool Parser::isAcceptable(Type type, std::function<void()> func)
{
	if (lexer_->currentToken().type_ == type) {
		if (func) {
			func();
		}
		lexer_->getToken();
		return true;
	}
	else {
		return false;
	}
}

void Parser::isAcceptableOrThrow(Type type, std::function<void()> func)
{
	if (!isAcceptable(type, func)) {
		throw WrongTokenException(lexer_->currentToken(), { type });
	}
}

void Parser::funcDefParse()
{
	std::unique_ptr<FuncDef> func;
	
	isAcceptableOrThrow(TokenType::IDENTIFIER, [&](){
		func = std::make_unique<FuncDef>(lexer_->currentToken().value_);
	}
	);
    func = std::make_unique<FuncDef>(lexer_->currentToken().value_);
	isAcceptableOrThrow(TokenType::RND_BR_OP);
	parametersParse(*func);

	FuncDef* temp_func = func.get();
	prog_.addFunc(std::move(func));

	isAcceptableOrThrow(TokenType::CUR_BR_OP);
	blockStateParse(temp_func->getFuncBlock());
}

void Parser::parametersParse(FuncDef& func)
{
	if (isAcceptable(TokenType::IDENTIFIER, [&]() {func.addParameter(lexer_->currentToken().value_); })) {
        func.addParameter(lexer_->currentToken().value_);
        while (isAcceptable(TokenType::COMMA) ){
			isAcceptable(TokenType::IDENTIFIER, [&] {func.addParameter(lexer_->currentToken().value_); });
		}
	}
	isAcceptableOrThrow(TokenType::RND_BR_CL);
}

void Parser::blockStateParse(BlockStatement & block)
{
	Token pars_tok = Token::unidentifiedType();
	std::unordered_map<TokenType, std::function<void()> > statementsList = {
		{TokenType::IDENTIFIER,		[&]() {
				block.addInstr(std::move(funcCallOrAssinStatemOrInitStatemParse(pars_tok) ) );
				isAcceptableOrThrow(Type::SEMICOLON);
			} 
		},
			
		{ TokenType::IF,		[&]() {
				block.addInstr(std::move(ifStatemParse() ));
			}
		},
		{ TokenType::FOR,		[&]() {
			block.addInstr(std::move(loopStatemParse(pars_tok)));
		}
		},
		{ TokenType::FOR_EAC,		[&]() {
			block.addInstr(std::move(loopStatemParse(pars_tok)));
		}
		}
	};

	while (!isAcceptable(Type::CUR_BR_CL)) {
		pars_tok = lexer_->currentToken();
		lexer_->getToken();

		if (statementsList.find(pars_tok.type_) != statementsList.end()) {
			statementsList.at(pars_tok.type_)();
		}
		else {
			throw WrongTokenException(pars_tok, { Type::IDENTIFIER, Type::IF, Type::FOR, Type::FOR_EAC, Type::RET });
		}
	}
	//lexer_->getToken();
}

StatemPtr Parser::funcCallOrAssinStatemOrInitStatemParse(Token token)
{
	StatemPtr ret_statem;
	if (isAcceptable(TokenType::RND_BR_OP)) {
		ret_statem = std::move(funcCallParse(token));

		if (isAcceptable(Type::PERIODIC_OP)) {
			ret_statem = std::move(perioFuncCallParse(token, std::move(ret_statem)));
		}
	}
	else {
		ret_statem = std::move(assignOrGraphicStatemParse(token) );
	}

	return ret_statem;

}

StatemPtr Parser::ifStatemParse()
{
	StatemPtr ret_statem;
	ExprPtr condit_expr;
	BlockPtr if_block;
	BlockPtr else_block;

	isAcceptableOrThrow(Type::RND_BR_OP);
	condit_expr = std::move(logicExprParse());
	isAcceptableOrThrow(Type::RND_BR_CL);

	isAcceptableOrThrow(Type::CUR_BR_OP);
	if_block = std::make_unique<BlockStatement>(block_);
	blockStateParse(*if_block);

	if (isAcceptable(Type::ELSE)) {
		isAcceptableOrThrow(Type::CUR_BR_OP);
		else_block = std::make_unique<BlockStatement>(block_);
		blockStateParse(*else_block);
		return std::make_unique<IfStatement>(std::move(condit_expr), std::move(if_block), std::move(else_block));
	}

	return std::make_unique<IfStatement>(std::move(condit_expr), std::move(if_block));
}

StatemPtr Parser::funcCallParse(Token token)
{
	if ( !prog_.isVaildFunc(token.value_)) {
		throw Exception(token.value_ + "is not a valid function identifier.");
	}

	FuncDef &func_def = prog_.getFuncDef(token.value_);		//TODO
	std::unique_ptr<FuncCall>  func_call = std::make_unique<FuncCall>(func_def); 

	if (!isAcceptable(Type::RND_BR_CL)) {
		func_call->addParam(logicExprParse());
		while (!isAcceptable(Type::RND_BR_CL)) {
			isAcceptableOrThrow(Type::COMMA);
			func_call->addParam(logicExprParse());
		}
	}

	if (func_call->paramCount() != func_def.paramCount()) {
		throw Exception(token.value_ + "function parameters doesnt match function deffinition" + "at" + token.getPos());
	}

	return std::move(func_call);
	//return StatemPtr();
}

StatemPtr Parser::perioFuncCallParse(Token token, StatemPtr func_call)
{
	ExprPtr expr;
	isAcceptableOrThrow(Type::RND_BR_OP);
	expr = std::move(logicExprParse());
	isAcceptableOrThrow(Type::RND_BR_CL);

	return std::make_unique<PeriodicFuncCall>( std::move(func_call) , std::move( expr) );
}

StatemPtr Parser::loopStatemParse(Token loop_token)
{
	Token tok = lexer_->currentToken();
	ExprPtr logic_expr;
	StatemPtr init_instr;
	StatemPtr loop_instr;
	BlockPtr loop_block;

	if (loop_token.type_ == Type::FOR) {
		isAcceptableOrThrow(Type::RND_BR_OP);

		if(isAcceptable(Type::IDENTIFIER) ) {
			init_instr = std::move(funcCallOrAssinStatemOrInitStatemParse(lexer_->currentToken()));
		}
		else {
			throw WrongTokenException(lexer_->currentToken(), {Type::IDENTIFIER});
		}
		isAcceptableOrThrow(Type::SEMICOLON);
		logic_expr = std::move( logicExprParse() );

		isAcceptableOrThrow(Type::SEMICOLON);

		if(isAcceptable(Type::IDENTIFIER) ) {
			loop_instr = std::move(funcCallOrAssinStatemOrInitStatemParse(lexer_->currentToken()));
		}
		else {
			throw WrongTokenException(lexer_->currentToken(), {Type::IDENTIFIER});
		}
		isAcceptableOrThrow(Type::RND_BR_CL);

		isAcceptableOrThrow(Type::CUR_BR_OP);
		loop_block = std::make_unique<BlockStatement>(block_);
		blockStateParse(*loop_block);

		std::unique_ptr<ForStatement> for_statem = std::make_unique<ForStatement>(std::move(logic_expr),std::move(loop_block), std::move(init_instr), std::move(loop_instr));
		return std::move(for_statem);
	}
	else if (loop_token.type_ == Type::FOR_EAC) {
		std::string coll;
		std::string iter;

		//isAcceptableOrThrow(Type::IDENTIFIER, [&]() { coll = lexer_->getToken().value_; });

		if(isAcceptable(Type::IDENTIFIER) ) {
			coll = lexer_->currentToken().value_;
		}
		else {
			throw WrongTokenException(lexer_->currentToken(), {Type::IDENTIFIER});
		}

		isAcceptableOrThrow(Type::COLON);

		//isAcceptableOrThrow(Type::IDENTIFIER, [&]() { iter = lexer_->getToken().value_; });

		if(isAcceptable(Type::IDENTIFIER) ) {
			iter = lexer_->currentToken().value_;
		}
		else {
			throw WrongTokenException(lexer_->currentToken(), {Type::IDENTIFIER});
		}

		isAcceptableOrThrow(Type::CUR_BR_OP);
		loop_block = std::make_unique<BlockStatement>(block_);
		blockStateParse(*loop_block);

		std::unique_ptr<ForEachStatement> for_each_statem = std::make_unique<ForEachStatement>(coll, iter, std::move(loop_block));
		return std::move(for_each_statem);
	}

}

StatemPtr Parser::assignOrGraphicStatemParse(Token token)
{
	StatemPtr ret_state;
	ExprPtr index_expr;
	ExprPtr expr;
	Token graph_ident = lexer_->currentToken();

	if (isAcceptable(Type::SQR_BR_OP)) {
		index_expr = std::move(logicExprParse());
		isAcceptableOrThrow(Type::SQR_BR_CL);
	}

	if (isAcceptable(Type::ASN)) {
		ret_state = std::move(assignStatemParse(token, std::move(index_expr )));
	}
	else if (isAcceptable(Type::DRAW) || isAcceptable(Type::MOVE) || isAcceptable(Type::SCALE) || isAcceptable(Type::CHNGCOL)){
		ret_state = std::move(graphicStatemParse(graph_ident, std::move(index_expr)) );
	}
	else
	{
		if (!block_->isValidVar(token.value_)) {
			block_->addVar(token.value_, std::move(index_expr));
			return ret_state;
		}
		else {
			throw Exception("Variable already exist");
		}
	}
	return ret_state;
}

StatemPtr Parser::assignStatemParse(Token token, ExprPtr index)
{
	ExprPtr expr_assign = std::move(logicExprParse());

	if ( !block_->isValidVar(token.value_)) {
		block_->addVar(token.value_, std::move( index) );
	}

	std::unique_ptr<AssignStatement> assign_statem = std::make_unique<AssignStatement>(block_->findVar(token.value_), std::move(expr_assign), std::move(index ) );
	return std::move(assign_statem);
}

StatemPtr Parser::graphicStatemParse(Token token, ExprPtr index)
{
	StatemPtr graph_func;

	if(token.type_ == Type::DRAW) {
		graph_func = std::move(drawFuncParse(token, std::move(index)));
	}
	else if(token.type_ == Type::SCALE || token.type_ == Type::CHNGCOL || token.type_ == Type::MOVE){
		graph_func = std::move(otherGrpahFunParse(token, std::move(index)));
	}

	return graph_func;
}

StatemPtr Parser::drawFuncParse(Token token, ExprPtr index)
{
	std::unique_ptr<GraphFunc> graph_func;

	std::string func_type = lexer_->currentToken().value_;

	isAcceptableOrThrow(Type::POS);
	isAcceptableOrThrow(Type::RND_BR_OP);

	graph_func = std::make_unique<GraphFunc>(func_type);
	graph_func->addParam(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	graph_func->addParam(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	graph_func->addParam(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::RND_BR_CL);


	isAcceptableOrThrow(Type::COL);
	isAcceptableOrThrow(Type::RND_BR_OP);

	graph_func->addParam(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	graph_func->addParam(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	graph_func->addParam(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::RND_BR_CL);


	isAcceptableOrThrow(Type::DIM);
	isAcceptableOrThrow(Type::RND_BR_OP);

	graph_func->addParam(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	graph_func->addParam(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	graph_func->addParam(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::RND_BR_CL);


	return graph_func;
}

StatemPtr Parser::otherGrpahFunParse(Token token, ExprPtr index)
{
	std::unique_ptr<GraphFunc> graph_func;
	if ( token.type_ == Type::SCALE || token.type_ == Type::MOVE || token.type_ == Type::CHNGCOL) {
		std::string func_type = lexer_->currentToken().value_;
		isAcceptableOrThrow(Type::RND_BR_OP);

		graph_func = std::make_unique<GraphFunc>(func_type);

		graph_func->addParam(std::move(logicExprParse()));

		isAcceptableOrThrow(Type::COMMA);

		graph_func->addParam(std::move(logicExprParse()));

		isAcceptableOrThrow(Type::COMMA);

		graph_func->addParam(std::move(logicExprParse()));


		isAcceptableOrThrow(Type::RND_BR_CL);

	}
	return graph_func;
}

ExprPtr Parser::logicExprParse()
{
	std::unique_ptr<LogicExpression> logic_expr = std::make_unique<LogicExpression>(andExprParse());

	while (isAcceptable(Type::OR_OP)) {
		logic_expr->addAlternativeAddExpr(std::move(andExprParse()));
	}

	return std::move(logic_expr);
}

ExprPtr Parser::andExprParse()
{
	std::unique_ptr<AddExpression> and_expr = std::make_unique<AddExpression>(std::move(relatExprParse()));

	while (isAcceptable(Type::AND_OP) ){
		and_expr->addNewRelatExpr( std::move(relatExprParse() ) );
	}

	return std::move(and_expr);
}

ExprPtr Parser::relatExprParse()
{
	std::unique_ptr<RelatExpression> relat_expr = std::make_unique<RelatExpression>(std::move(simplLogicExprParse()));
	while (isAcceptable(Type::GOE_OP)
		|| isAcceptable(Type::GTH_OP)
		|| isAcceptable(Type::LOE_OP)
		|| isAcceptable(Type::LTH_OP)
		|| isAcceptable(Type::EQU_OP)
		|| isAcceptable(Type::NEQ_OP)) {
		relat_expr->addNextSimpleLogExpr(std::move(simplLogicExprParse()), lexer_->currentToken().type_);
	}
	return std::move(relat_expr);
}

ExprPtr Parser::simplLogicExprParse()
{
	if (isAcceptable(Type::NEG)) {
		return std::make_unique<SimpleLogicExpression>(std::move(assignableExprParse()), true );
	}else{
		return std::make_unique<SimpleLogicExpression>(std::move(assignableExprParse()) );
	}
}

ExprPtr Parser::assignableExprParse()
{
	std::unique_ptr<AssignableExpression> assnable_expr = std::make_unique<AssignableExpression>(std::move(multpExprParse()));
	
	while (isAcceptable(Type::ADD_OP) || isAcceptable (Type::SUB_OP) ){
		assnable_expr->addMultExpr(std::move(multpExprParse()), lexer_->currentToken().type_);
	}
	return std::move(assnable_expr);
}

ExprPtr Parser::multpExprParse()
{
	std::unique_ptr<MultipExpression> assnable_expr = std::make_unique<MultipExpression>(std::move(simplAssnbleExprParse()));

	while (isAcceptable(Type::MUL_OP) || isAcceptable (Type::DIV_OP) ){
		assnable_expr->addSimpleAssignExpr(std::move(simplAssnbleExprParse()), lexer_->currentToken().type_);
	}
	return std::move(assnable_expr);

}

ExprPtr Parser::simplAssnbleExprParse() {
	std::unique_ptr<Expresion> simple_assnable_expr;

	if (isAcceptable(Type::NUMBER)) {

		simple_assnable_expr = std::make_unique<SimpleAssnblExpression>(new Variable(lexer_->currentToken() ));
		//TODO fix this
	}
	else if (isAcceptable(Type::IDENTIFIER)) {
		Token ident = lexer_->currentToken();
		if (isAcceptable(Type::RND_BR_OP)) {
			simple_assnable_expr = std::make_unique<SimpleAssnblExpression>(std::move(funcCallParse(ident)));
		}
		else {
			if (isAcceptable(Type::SQR_BR_OP)) {
				ExprPtr index_expr;
				index_expr = std::move(logicExprParse());
				isAcceptableOrThrow(Type::SQR_BR_CL);
			}
			else {

				simple_assnable_expr = std::make_unique<SimpleAssnblExpression>(block_->findVar(ident.value_));
			}
		}
	}
	else {
		throw WrongTokenException(lexer_->currentToken(), { Type::IDENTIFIER, Type::NUMBER });
	}
	return simple_assnable_expr;
}

