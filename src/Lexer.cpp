#include "Lexer.h"
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include <unordered_map>

using Type = Guarduaux::TokenType;
using namespace Guarduaux;

Guarduaux::Lexer::Lexer(Input inp)
:	input_(inp), 
	lastch_(' '), 
	pos_(1, -1), 
	currentToken_(Token::unidentifiedType())
{
}

Guarduaux::Lexer::~Lexer()
{
}

void Guarduaux::Lexer::ignoreWhiteSpace() {
	while (std::isspace(lastch_))
		processNextChar();
}

void Guarduaux::Lexer::processNextChar() {
	if (lastch_ == '\n') {
		pos_.column_ = 0;
		++pos_.line_;
	}

	else
		++pos_.column_;

	lastch_ = input_.getNextChar();
}

void Guarduaux::Lexer::cacheNextChar() {
	buffer_ += lastch_;
	processNextChar();
}

Token & Guarduaux::Lexer::getToken() {
	currentToken_ = Token::unidentifiedType();

	ignoreWhiteSpace();
	currentToken_.setPos( pos_ );

	if(input_.isEndOfFile()){
		currentToken_ = TokenType ::END_OF_FILE;
	}

	tryIdentifier();
	if ( currentToken_.isVaild()) {
		buffer_.clear();
		return currentToken_;
	}

	tryNumber();
	if ( currentToken_.isVaild()) {
		buffer_.clear();
		return currentToken_;
	}

	tryOperator();
	if ( currentToken_.isVaild()) {
		buffer_.clear();
		return currentToken_;
	}

	trySpecialSign();
	if ( currentToken_.isVaild()) {
		buffer_.clear();
		return currentToken_;
	}
	else {
		cacheNextChar();
		currentToken_.value_ = buffer_;
	}

	buffer_.clear();
	return currentToken_ ;
}

Token & Guarduaux::Lexer::currentToken()
{
	return currentToken_;
}

void Guarduaux::Lexer::tryIdentifier() {
	Token ret_tok = Token::unidentifiedType();

	if (std::isalpha(lastch_) || lastch_ == '_') {
		int length = 1;
		cacheNextChar();

		while (std::isalnum(lastch_) || lastch_ == '_') {
			cacheNextChar();

			if (++length > IDENTIFIER_MAX_LENGTH) {
				throw std::runtime_error("Maximum identifier lenght");
			}
		}
	}
	else {
		return; // identifier not found
	}
	tryKeyword();
	if (currentToken_.isVaild()) {
		return;
	}

	currentToken_.type_ = Type::IDENTIFIER;
	currentToken_.value_ = buffer_;
}

void Guarduaux::Lexer::tryKeyword() {
	static const std::unordered_map<std::string, TokenType> &keyword_types = {
			{ "func", TokenType ::FUNC },
			{ "return", TokenType ::RET },
			{"if", TokenType::IF },
			{ "else", TokenType::ELSE },
			{"for", TokenType::FOR },
			{"for_each", TokenType::FOR_EAC },
			{"draw", TokenType::DRAW },
			{"scale", TokenType::SCALE },
			{"move", TokenType::MOVE },
			{"chngcol", TokenType::CHNGCOL },
			{"box", TokenType::BOX },
			{"sphere", TokenType::SPHERE },
			{"dim", TokenType::DIM },
			{"col", TokenType::COL },
			{"pos", TokenType::POS }
	};
	auto type = keyword_types.find(buffer_);
	if( type != keyword_types.end()){
		currentToken_.type_ = type -> second;
		currentToken_.value_ = type ->first;
	}

}


void Guarduaux::Lexer::tryNumber() {

	if (std::isdigit(lastch_)) {
		cacheNextChar();

		while (std::isdigit(lastch_)) {
			cacheNextChar();
		}

		currentToken_.type_ = Type::NUMBER;
		currentToken_.value_ = buffer_;
	}

}

void Guarduaux::Lexer::tryOperator() {

	tryPeriodicalOp();
	if (currentToken_.isVaild()) {
		return;
	}

	tryMultiOp();
	if (currentToken_.isVaild()) {
		return;
	}

	tryAddtvOp();
	if (currentToken_.isVaild()) {
		return;
	}

	tryEqualOp();
	if (currentToken_.isVaild()) {
		return;
	}

	tryLogicOp();
	if (currentToken_.isVaild()) {
		return;
	}

	tryRelatOp();
	if (currentToken_.isVaild()) {
		return;
	}
}

void Guarduaux::Lexer::tryPeriodicalOp() {

	if (lastch_ == '~') {
		cacheNextChar();

		currentToken_.type_ = Type::PERIODIC_OP;
		currentToken_.value_ = '~';
	}
}

void Guarduaux::Lexer::tryMultiOp() {

	if (lastch_ == '*') {
		cacheNextChar();

		currentToken_.type_ = Type::MUL_OP;
		currentToken_.value_ = '*';
	} 
	else if (lastch_ == '/') {
		cacheNextChar();

		currentToken_.type_ = Type::DIV_OP;
		currentToken_.value_ = '/';
	}
}

void Guarduaux::Lexer::tryAddtvOp() {

	if (lastch_ == '+') {
		cacheNextChar();

		currentToken_.type_ = Type::ADD_OP;
		currentToken_.value_ = '+';
	}
	else if (lastch_ == '-') {
		cacheNextChar();

		currentToken_.type_ = Type::SUB_OP;
		currentToken_.value_ = '-';
	}
}

void Guarduaux::Lexer::tryEqualOp() {

	if (lastch_ == '!') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '=') {
			cacheNextChar();
			cacheNextChar();

			currentToken_.type_ = Type::NEQ_OP;
			currentToken_.value_ = "!=";
		}
		else {
			cacheNextChar();

			currentToken_.type_ = Type::NEG;
			currentToken_.value_ = "!";
		}
	}
	else if (lastch_ == '=') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '=') {
			cacheNextChar();
			cacheNextChar();

			currentToken_.type_ = Type::EQU_OP;
			currentToken_.value_ = "==";
		}
		else {
			cacheNextChar();

			currentToken_.type_ = Type::ASN;
			currentToken_.value_ = '=';
		}
	}
}

void Guarduaux::Lexer::tryLogicOp() {

	if (lastch_ == '&') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '&') {
			cacheNextChar();
			cacheNextChar();

			currentToken_.type_ = Type::AND_OP;
			currentToken_.value_ = "&&";
		}
		
	}
	else if (lastch_ == '|') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '|') {
			cacheNextChar();
			cacheNextChar();

			currentToken_.type_ = Type::OR_OP;
			currentToken_.value_ = "||";
		}
		
	}
}

void Guarduaux::Lexer::tryRelatOp() {

	if (lastch_ == '>') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '=') {
			cacheNextChar();
			cacheNextChar();

			currentToken_.type_ = Type::GOE_OP;
			currentToken_.value_ = ">=";
		}
		else {
			cacheNextChar();

			currentToken_.type_ = Type::GTH_OP;
			currentToken_.value_ = ">";
		}
	}
	else if (lastch_ == '<') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '=') {
			cacheNextChar();
			cacheNextChar();

			currentToken_.type_ = Type::LOE_OP;
			currentToken_.value_ = "<=";
		}
		else {
			cacheNextChar();

			currentToken_.type_ = Type::LTH_OP;
			currentToken_.value_ = "<";
		}
	}
}

void Guarduaux::Lexer::trySpecialSign() {

	static const std::unordered_map<char , TokenType> &special_sing_types = {
			{'{', TokenType::CUR_BR_OP},
			{'}', TokenType::CUR_BR_CL},
			{'[', TokenType::SQR_BR_OP },
			{']', TokenType::SQR_BR_CL },
			{'(', TokenType::RND_BR_OP },
			{')', TokenType::RND_BR_CL },
			{',', TokenType::COMMA },
			{'.', TokenType::DOT },
			{':', TokenType::COLON },
			{';', TokenType::SEMICOLON }
	};

	auto type = special_sing_types.find(lastch_);
	if(type != special_sing_types.end()){
		currentToken_.type_ = type->second;
		currentToken_.value_ = type->first;
		cacheNextChar();
	}
}
