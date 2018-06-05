#include "Parser.h"

#include <memory>
#include <unordered_map>
#include <list>
#include <functional>

#include <Program/Program.h>
#include "Expresions/Expresion.h"
#include "Program/Exception.h"
#include "Program/Variable.h"
#include "Statements/FuncCall.h"
#include "Program/FuncDef.h"
#include "Statements/IfStatement.h"
#include "Statements/AssignStatement.h"
#include "Statements/ForStatement.h"
#include "Statements/PeriodicFuncCall.h"
#include "Expresions/LogicExpression.h"
#include "Expresions/AndExpression.h"
#include "Expresions/RelatExpression.h"
#include "Expresions/SimpleLogicExpression.h"
#include "Expresions/AssignableExpression.h"
#include "Expresions/SimpleAssnblExpression.h"
#include "Expresions/MultipExpression.h"
#include "Statements/ReturnStatement.h"
#include "Statements/DrawGraphicFunc.h"
#include "Statements/ScaleGraphFunc.h"
#include "Statements/MoveGraphFunc.h"
#include "Statements/ChngcolGraphFunc.h"

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

Program & Parser::parse()
{
	if (lexer_) {
		lexer_->getToken();
		parseProgram();
		return prog_;
	}
	else {
	    throw Exception("Lexer not found.");
	}
}

void Parser::parseProgram()
{
	while (lexer_->currentToken().type_ != Type::END_OF_FILE  ) {

		if (isAcceptable(Type::FUNC)) {
			prog_.addFunc(std::move(funcDefParse()));
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

std::unique_ptr<FuncDef> Parser::funcDefParse()
{
	std::unique_ptr<FuncDef> func;
	std::string func_name;
	isAcceptableOrThrow(TokenType::IDENTIFIER, [&]()  {
		func_name = lexer_->currentToken().value_;
	});


	isAcceptableOrThrow(TokenType::RND_BR_OP);
	std::vector<std::string>param_vector = parametersParse();
	isAcceptableOrThrow(TokenType::RND_BR_CL);

	currContext_ = new Context(param_vector);
	BlockPtr block_statem = std::move(blockStateParse() );

	delete currContext_;
	return std::move(std::make_unique<FuncDef>(func_name, param_vector, std::move(block_statem) ) );
}

std::vector<std::string> Parser::parametersParse()
{
	std::vector<std::string> param_vector;
	if (isAcceptable(TokenType::IDENTIFIER , [&] () {
		param_vector.push_back(lexer_->currentToken().value_);
	})) {
        while (isAcceptable(TokenType::COMMA) ){
			isAcceptable(TokenType::IDENTIFIER, [&] {param_vector.push_back(lexer_->currentToken().value_); });
		}
	}

	return param_vector;
}

BlockPtr Parser::blockStateParse()
{
	isAcceptableOrThrow(TokenType::CUR_BR_OP);
	Context* old_context = currContext_;
	BlockPtr curr_block = std::make_unique<BlockStatement>(currContext_);
	currContext_ =  curr_block->getContext_().get();

	Token pars_tok = Token::unidentifiedType();

	 std::unordered_map<TokenType, std::function<void()> > statements_list = {
		{TokenType::IDENTIFIER,		[&]() {
			StatemPtr inst = funcCallOrAssinStatemOrInitStatemParse(pars_tok);
			if(inst){
				curr_block->addInstr(std::move(inst ) );

			}
				isAcceptableOrThrow(Type::SEMICOLON);
			} 
		},
			
		{ TokenType::IF,		[&]() {
			curr_block->addInstr(std::move(ifStatemParse() ));
			}
		},
		{ TokenType::FOR,		[&]() {
			curr_block->addInstr(std::move(loopStatemParse(pars_tok)));
		}
		},
		{ TokenType::RET,		[&]() {
		    curr_block->addInstr(std::move(returnStatemParse()));
		    isAcceptableOrThrow(Type::SEMICOLON);
		    }
		}
	};

	while (!isAcceptable(Type::CUR_BR_CL)) {
		pars_tok = lexer_->currentToken();
		lexer_->getToken();

		if (statements_list.find(pars_tok.type_) != statements_list.end()) {
			statements_list.at(pars_tok.type_)();
		}
		else {
			throw WrongTokenException(pars_tok, { Type::IDENTIFIER, Type::IF, Type::FOR, Type::RET });
		}
	}

	currContext_ = old_context;

	return std::move(curr_block);
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

	if_block = blockStateParse();

	if (isAcceptable(Type::ELSE)) {
		else_block = blockStateParse();
		return std::make_unique<IfStatement>(std::move(condit_expr), std::move(if_block), std::move(else_block));
	}
	else{
		return std::make_unique<IfStatement>(std::move(condit_expr), std::move(if_block));
	}
}

StatemPtr Parser::funcCallParse(Token token)
{
	if ( !prog_.isVaildFunc(token.value_)) {
		throw Exception(token.value_ + "is not a valid function identifier.");
	}

	std::shared_ptr<FuncDef> func_def = prog_.getFuncDef(token.value_);
    std::vector<std::unique_ptr<Expresion> > parameters;
	if (!isAcceptable(Type::RND_BR_CL)) {

        parameters.push_back(logicExprParse());
		while (!isAcceptable(Type::RND_BR_CL)) {
			isAcceptableOrThrow(Type::COMMA);
			parameters.push_back(logicExprParse());
		}
	}

	if (parameters.size() != func_def->paramCount()) {
		throw Exception(token.value_ + "function parameters doesnt match function deffinition" + "at" + token.getPos().toString());
	}


	return std::make_unique<FuncCall>(func_def , std::move(parameters));
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
	Token tok = Token::unidentifiedType();
	ExprPtr logic_expr;
	StatemPtr init_instr;
	StatemPtr loop_instr;
	BlockPtr loop_block;

	isAcceptableOrThrow(Type::RND_BR_OP);

	if(isAcceptable(Type::IDENTIFIER, [&]() {
		tok = lexer_->currentToken();
	} )  ){
		init_instr = std::move(funcCallOrAssinStatemOrInitStatemParse(tok));
	}
	else {
		throw WrongTokenException(lexer_->currentToken(), {Type::IDENTIFIER});
	}
	isAcceptableOrThrow(Type::SEMICOLON);
	logic_expr = std::move( logicExprParse() );

	isAcceptableOrThrow(Type::SEMICOLON);

	if(isAcceptable(Type::IDENTIFIER, [&]() {
       tok = lexer_->currentToken();
    } )  ){
		loop_instr = std::move(funcCallOrAssinStatemOrInitStatemParse(tok));
	}
	else {
		throw WrongTokenException(lexer_->currentToken(), {Type::IDENTIFIER});
	}
	isAcceptableOrThrow(Type::RND_BR_CL);

	loop_block = std::move(blockStateParse());
	std::unique_ptr<ForStatement> for_statem = std::make_unique<ForStatement>(std::move(logic_expr),std::move(loop_block), std::move(init_instr), std::move(loop_instr));
	return std::move(for_statem);
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
		ret_state = std::move(graphicStatemParse(graph_ident, token, std::move(index_expr)) );
	}
	else
	{
		if (!currContext_->isValidVar(token.value_)) {
			currContext_->addVar(token.value_, std::move(index_expr));
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

	if ( !currContext_->isValidVar(token.value_)) {
		currContext_->addVar(token.value_, std::move( index) );
	}

	std::unique_ptr<AssignStatement> assign_statem = std::make_unique<AssignStatement>(currContext_->findVar(token.value_), std::move(expr_assign), std::move(index ) );
	return std::move(assign_statem);
}

StatemPtr Parser::graphicStatemParse(Token token, Token var_name ,ExprPtr index)
{
	StatemPtr graph_func;

	if(token.type_ == Type::DRAW) {
		graph_func = std::move(drawFuncParse(var_name, std::move(index)));
	}
	else if(token.type_ == Type::SCALE || token.type_ == Type::CHNGCOL || token.type_ == Type::MOVE){
		graph_func = std::move(otherGrpahFunParse(token, var_name, std::move(index)));
	}

	return graph_func;
}

StatemPtr Parser::drawFuncParse(Token token, ExprPtr index)
{
    std::vector<std::unique_ptr<Expresion> > position;
    std::vector<std::unique_ptr<Expresion> > dimension;
    std::vector<std::unique_ptr<Expresion> > color;

	Token func_type = lexer_->currentToken();

	Token graph_obj_type = Token::unidentifiedType();

	if(isAcceptable(Type::BOX) || isAcceptable(Type::CYLINDER)){
	    graph_obj_type = lexer_->currentToken();
	}
	else {
	    throw WrongTokenException(lexer_->currentToken(), {Type::BOX, Type::CYLINDER});
	}

	isAcceptableOrThrow(Type::POS);
	isAcceptableOrThrow(Type::RND_BR_OP);

	position.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

    position.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

    position.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::RND_BR_CL);


	isAcceptableOrThrow(Type::COL);
	isAcceptableOrThrow(Type::RND_BR_OP);

	color.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

    color.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

    color.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::RND_BR_CL);


	isAcceptableOrThrow(Type::DIM);
	isAcceptableOrThrow(Type::RND_BR_OP);

	dimension.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

    dimension.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

    dimension.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::RND_BR_CL);

	currContext_->addObj(token.value_, func_type);

	return std::move(std::make_unique<DrawGraphicFunc>(func_type.value_ ,token.value_, std::move(position), std::move(dimension), std::move(color) ));
}

StatemPtr Parser::otherGrpahFunParse(Token token, Token var_name, ExprPtr index)
{
	if(token.type_ == Type::SCALE){
		return std::move(scaleFuncParse(var_name, std::move(index) ));
	}
	else if(token.type_ == Type::MOVE){
		return std::move(moveFuncParse(var_name, std::move(index) ));
	}
	else if(token.type_ == Type::CHNGCOL){
		return std::move(chngcolFuncParse(var_name, std::move(index) ));
	}
	else {
		WrongTokenException(token, { Type::DRAW, Type::SCALE, Type::CHNGCOL, Type::MOVE });
	}
}

StatemPtr Parser::scaleFuncParse(Token var_name, ExprPtr index) {

	std::vector<std::unique_ptr<Expresion> > coord;

	isAcceptableOrThrow(Type::RND_BR_OP);

	coord.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	coord.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	coord.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::RND_BR_CL);

	return std::move(std::make_unique<ScaleGraphicFunc>(currContext_->findObj(var_name.value_), std::move(coord)));
}

StatemPtr Parser::moveFuncParse(Token var_name, ExprPtr index) {
	std::vector<std::unique_ptr<Expresion> > coord;

	isAcceptableOrThrow(Type::RND_BR_OP);

	coord.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	coord.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	coord.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::RND_BR_CL);
	return std::move(std::make_unique<MoveGraphicFunc>(currContext_->findObj(var_name.value_) , std::move(coord)));
}

StatemPtr Parser::chngcolFuncParse(Token var_name, ExprPtr index) {
	std::vector<std::unique_ptr<Expresion> > col;

	isAcceptableOrThrow(Type::RND_BR_OP);

	col.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	col.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::COMMA);

	col.push_back(std::move(logicExprParse()));

	isAcceptableOrThrow(Type::RND_BR_CL);

	return std::move(std::make_unique<ChngcolGraphicFunc>(currContext_->findObj(var_name.value_), std::move(col)));
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
	std::unique_ptr<AndExpression> and_expr = std::make_unique<AndExpression>(std::move(relatExprParse()));

	while (isAcceptable(Type::AND_OP) ){
		and_expr->addNewRelatExpr( std::move(relatExprParse() ) );
	}

	return std::move(and_expr);
}

ExprPtr Parser::relatExprParse()
{
	std::unique_ptr<RelatExpression> relat_expr = std::make_unique<RelatExpression>(std::move(simplLogicExprParse()));
	while (lexer_->currentToken().type_ ==(Type::GOE_OP)
		|| lexer_->currentToken().type_ ==(Type::GTH_OP)
		|| lexer_->currentToken().type_ ==(Type::LOE_OP)
		|| lexer_->currentToken().type_ ==(Type::LTH_OP)
		|| lexer_->currentToken().type_ ==(Type::EQU_OP)
		|| lexer_->currentToken().type_ ==(Type::NEQ_OP)) {

		if(isAcceptable(Type::GOE_OP)){
			relat_expr->addNextSimpleLogExpr(std::move(simplLogicExprParse()), Type::GOE_OP);
		}
		else if(isAcceptable(Type::GTH_OP)){
			relat_expr->addNextSimpleLogExpr(std::move(simplLogicExprParse()), Type::GTH_OP);
		}
		else if(isAcceptable(Type::LOE_OP)){
			relat_expr->addNextSimpleLogExpr(std::move(simplLogicExprParse()), Type::LOE_OP);
		}
		else if(isAcceptable(Type::LTH_OP)){
			relat_expr->addNextSimpleLogExpr(std::move(simplLogicExprParse()), Type::LTH_OP);
		}
		else if(isAcceptable(Type::EQU_OP)){
			relat_expr->addNextSimpleLogExpr(std::move(simplLogicExprParse()), Type::EQU_OP);
		}
		else if(isAcceptable(Type::NEQ_OP)){
			relat_expr->addNextSimpleLogExpr(std::move(simplLogicExprParse()), Type::NEQ_OP);
		}

	}
	return std::move(relat_expr);
}

ExprPtr Parser::simplLogicExprParse()
{
	if (isAcceptable(Type::NEG)) {
		return std::make_unique<SimpleLogicExpression>(std::move(assignableExprParse()), true );
	}else{
		return std::move(std::make_unique<SimpleLogicExpression>(std::move(assignableExprParse()) ) );
	}
}

ExprPtr Parser::assignableExprParse()
{
	std::unique_ptr<AssignableExpression> assnable_expr = std::make_unique<AssignableExpression>(std::move(multpExprParse()));
	
	while (lexer_->currentToken().type_ == (Type::ADD_OP) || lexer_->currentToken().type_ == (Type::SUB_OP) ){
		if( isAcceptable(Type::ADD_OP) ){
			assnable_expr->addMultExpr(std::move(multpExprParse()), TokenType::ADD_OP);
		}
		else if (  isAcceptable(Type::SUB_OP) ) {
			assnable_expr->addMultExpr(std::move(multpExprParse()), TokenType::SUB_OP);
		}

	}
	return std::move(assnable_expr);
}

ExprPtr Parser::multpExprParse()
{
	std::unique_ptr<MultipExpression> assnable_expr = std::make_unique<MultipExpression>(
			std::move(simplAssnbleExprParse()));

	while (lexer_->currentToken().type_ == (Type::MUL_OP) || lexer_->currentToken().type_ ==  (Type::DIV_OP) ){
		if(isAcceptable(TokenType::MUL_OP)) {
			assnable_expr->addSimpleAssignExpr(std::move(simplAssnbleExprParse()), Type::MUL_OP);
		}
		else if(isAcceptable(TokenType::DIV_OP)) {
			assnable_expr->addSimpleAssignExpr(std::move(simplAssnbleExprParse()), Type::DIV_OP);
		}
	}
	return std::move(assnable_expr);

}

ExprPtr Parser::simplAssnbleExprParse() {
    Token ident = Token::unidentifiedType();
	std::unique_ptr<Expresion> simple_assnable_expr;

	std::unique_ptr<Variable> number_var = numberParse();
	if ( number_var ) {
		simple_assnable_expr = std::make_unique<SimpleAssnblExpression>( std::make_shared<Variable>(*number_var) );
	}
	else if (isAcceptable(Type::IDENTIFIER, [&]() {
        ident = lexer_->currentToken();
	}) )
	{
		if (isAcceptable(Type::RND_BR_OP)) {
			simple_assnable_expr = std::make_unique<SimpleAssnblExpression>(std::move(funcCallParse(ident)));
		}
		else {
			if (isAcceptable(Type::SQR_BR_OP)) {
				ExprPtr index_expr;
				index_expr = std::move(logicExprParse());
				isAcceptableOrThrow(Type::SQR_BR_CL);

				simple_assnable_expr = std::make_unique<SimpleAssnblExpression>(
						currContext_->findVar(ident.value_),std::move(index_expr)  );
			}
			else {

				simple_assnable_expr = std::make_unique<SimpleAssnblExpression>(currContext_->findVar(ident.value_) );
			}
		}
	}
	else {
		throw WrongTokenException(lexer_->currentToken(), { Type::IDENTIFIER, Type::NUMBER });
	}
	return std::move(simple_assnable_expr);
}

StatemPtr Parser::returnStatemParse() {
    auto return_statem = std::make_unique<ReturnStatem>(std::move(logicExprParse()));
	return std::move(return_statem);
}

std::unique_ptr<Variable> Parser::numberParse() {
	std::unique_ptr<Variable> number_var;
    bool isNegativ =  isAcceptable(Type::MINUS);
    if( isNegativ){
		int number;
		isAcceptableOrThrow(Type::NUMBER, [&]() {
			number = std::stoi(lexer_->currentToken().value_) ;
		});

		number_var = std::make_unique<Variable>(-number);
		return std::move(number_var);
    }
    else {
		int number;
    	if(isAcceptable(Type::NUMBER, [&]() {
				number = std::stoi(lexer_->currentToken().value_) ;})  ){
			 number_var = std::make_unique<Variable>(number);
			return std::move(number_var);
    	}
    	else{
			return std::move(number_var);
    	}
    }



}




