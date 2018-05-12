#include "Lexer.h"
#include <cstdlib>
#include <cctype>
#include <stdexcept>

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

Token Guarduaux::Lexer::getToken() {
	Token ret_tok = Token::unidentifiedType();

	ignoreWhiteSpace();
	Position temp_pos = pos_;
	if(input_.isEndOfFile()){
		ret_tok = TokenType ::END_OF_FILE;
	}
	else if ( ( ret_tok = tryIdentifier() ).isVaild()) {}
	else if ( (ret_tok = tryNumber() ).isVaild()) {}
	else if ((ret_tok = tryOperator()).isVaild()) {}
	else if ((ret_tok = trySpecialSign()).isVaild()) {}
	else {
		cacheNextChar();
		ret_tok.value_ = buffer_;
	}

	ret_tok.setPos(temp_pos);
	buffer_.clear();
	return currentToken_ = ret_tok;
}

Token Guarduaux::Lexer::currentToken() const
{
	return currentToken_;
}

Token Guarduaux::Lexer::tryIdentifier() {
	Token ret_tok = Token::unidentifiedType();

	if (std::isalpha(lastch_) || lastch_ == '_') {
		int length = 1;
		cacheNextChar();

		while (std::isalpha(lastch_) || lastch_ == '_') {
			cacheNextChar();

			if (++length > IDENTIFIER_MAX_LENGTH) {
				throw std::runtime_error("Maximum identifier lenght");
			}
		}
	}
	else {
		return ret_tok; // identifier not found 
	}

	if ((ret_tok = tryKeyword()).isVaild()) {
		return ret_tok;
	}

	ret_tok.type_ = Type::IDENTIFIER;
	ret_tok.value_ = buffer_;

	return ret_tok;
}

Token Guarduaux::Lexer::tryKeyword() {
	Token ret_tok = Token::unidentifiedType();
	
	if ( (ret_tok = tryFunc()).isVaild() ) {
		return ret_tok;
	}

	if ((ret_tok = tryReturn()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryIf()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryElse()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryFor()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryForEach()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryDraw()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryScale()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryMove()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryChngCol()).isVaild()) {
		return ret_tok;
	}
	
	if ((ret_tok = tryBox()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = trySphere()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryDim()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryPos()).isVaild()) {
		return ret_tok;
	}

	if ((ret_tok = tryCol()).isVaild()) {
		return ret_tok;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryFunc() {
	Token ret_tok = Token::unidentifiedType();
	
	if (buffer_ == "func") {
		ret_tok.type_ = Type::FUNC;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryReturn() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "return") {
		ret_tok.type_ = Type::RET;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryIf() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "if") {
		ret_tok.type_ = Type::IF;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryElse() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "else") {
		ret_tok.type_ = Type::ELSE;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryFor() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "for") {
		ret_tok.type_ = Type::FOR;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryForEach() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "for_each") {
		ret_tok.type_ = Type::FOR_EAC;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryDraw() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "draw") {
		ret_tok.type_ = Type::DRAW;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryScale() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "scale") {
		ret_tok.type_ = Type::SCALE;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryMove() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "move") {
		ret_tok.type_ = Type::MOVE;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryChngCol() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "chngcol") {
		ret_tok.type_ = Type::CHNGCOL;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryBox() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "box") {
		ret_tok.type_ = Type::BOX;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::trySphere() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "sphere") {
		ret_tok.type_ = Type::SPHERE;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryDim() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "dim") {
		ret_tok.type_ = Type::DIM;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryCol() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "col") {
		ret_tok.type_ = Type::COL;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryPos() {
	Token ret_tok = Token::unidentifiedType();

	if (buffer_ == "pos") {
		ret_tok.type_ = Type::POS;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryNumber() {
	Token ret_tok = Token::unidentifiedType();

	if (lastch_ == '-') {
		char peek_char = input_.peekNextChar();

		if (std::isdigit(peek_char) ){
			cacheNextChar();

			while (std::isdigit(lastch_)){
				cacheNextChar();
			}

			ret_tok.type_ = Type::NEG_NUMBER;
			ret_tok.value_ = buffer_;
		}
	}
	else if (std::isdigit(lastch_)) {
		cacheNextChar();

		while (std::isdigit(lastch_)) {
			cacheNextChar();
		}

		ret_tok.type_ = Type::NUMBER;
		ret_tok.value_ = buffer_;
	}

	return ret_tok;
	

}

Token Guarduaux::Lexer::tryOperator() {
	Token ret_tok = Token::unidentifiedType();

	if ((ret_tok = tryPeriodicalOp()).isVaild()) {}
	else if ((ret_tok = tryMultiOp()).isVaild()) {}
	else if ((ret_tok = tryAddtvOp()).isVaild()) {}
	else if ((ret_tok = tryEqualOp()).isVaild()) {}
	else if ((ret_tok = tryLogicOp()).isVaild()) {}
	else if ((ret_tok = tryRelatOp()).isVaild()) {}
	return ret_tok;
}

Token Guarduaux::Lexer::tryPeriodicalOp() {
	Token ret_tok = Token::unidentifiedType();

	if (lastch_ == '~') {
		cacheNextChar();

		ret_tok.type_ = Type::PERIODIC_OP;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryMultiOp() {
	Token ret_tok = Token::unidentifiedType();

	if (lastch_ == '*') {
		cacheNextChar();

		ret_tok.type_ = Type::MUL_OP;
		ret_tok.value_ = buffer_;
	} 
	else if (lastch_ == '/') {
		cacheNextChar();

		ret_tok.type_ = Type::DIV_OP;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryAddtvOp() {
	Token ret_tok = Token::unidentifiedType();

	if (lastch_ == '+') {
		cacheNextChar();

		ret_tok.type_ = Type::ADD_OP;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == '-') {
		cacheNextChar();

		ret_tok.type_ = Type::SUB_OP;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryEqualOp() {
	Token ret_tok = Token::unidentifiedType();

	if (lastch_ == '!') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '=') {
			cacheNextChar();
			cacheNextChar();

			ret_tok.type_ = Type::NEQ_OP;
			ret_tok.value_ = buffer_;
		}
		else {
			cacheNextChar();

			ret_tok.type_ = Type::NEG;
			ret_tok.value_ = buffer_;
		}
	}
	else if (lastch_ == '=') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '=') {
			cacheNextChar();
			cacheNextChar();

			ret_tok.type_ = Type::EQU_OP;
			ret_tok.value_ = buffer_;
		}
		else {
			cacheNextChar();

			ret_tok.type_ = Type::ASN;
			ret_tok.value_ = buffer_;
		}
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryLogicOp() {
	Token ret_tok = Token::unidentifiedType();

	if (lastch_ == '&') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '&') {
			cacheNextChar();
			cacheNextChar();

			ret_tok.type_ = Type::AND_OP;
			ret_tok.value_ = buffer_;
		}
		
	}
	else if (lastch_ == '|') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '|') {
			cacheNextChar();
			cacheNextChar();

			ret_tok.type_ = Type::OR_OP;
			ret_tok.value_ = buffer_;
		}
		
	}
	return ret_tok;
}

Token Guarduaux::Lexer::tryRelatOp() {
	Token ret_tok = Token::unidentifiedType();

	if (lastch_ == '>') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '=') {
			cacheNextChar();
			cacheNextChar();

			ret_tok.type_ = Type::GOE_OP;
			ret_tok.value_ = buffer_;
		}
		else {
			cacheNextChar();

			ret_tok.type_ = Type::GTH_OP;
			ret_tok.value_ = buffer_;
		}
	}
	else if (lastch_ == '<') {
		char peek_char = input_.peekNextChar();

		if (peek_char == '=') {
			cacheNextChar();
			cacheNextChar();

			ret_tok.type_ = Type::LOE_OP;
			ret_tok.value_ = buffer_;
		}
		else {
			cacheNextChar();

			ret_tok.type_ = Type::LTH_OP;
			ret_tok.value_ = buffer_;
		}
	}
	return ret_tok;
}

Token Guarduaux::Lexer::trySpecialSign() {
	Token ret_tok = Token::unidentifiedType();

	if (lastch_ == '{') {
		cacheNextChar();

		ret_tok.type_ = Type::CUR_BR_OP;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == '}') {
		cacheNextChar();

		ret_tok.type_ = Type::CUR_BR_CL;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == '[') {
		cacheNextChar();

		ret_tok.type_ = Type::SQR_BR_OP;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == ']') {
		cacheNextChar();

		ret_tok.type_ = Type::SQR_BR_CL;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == '(') {
		cacheNextChar();

		ret_tok.type_ = Type::RND_BR_OP;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == ')') {
		cacheNextChar();

		ret_tok.type_ = Type::RND_BR_CL;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == ',') {
		cacheNextChar();

		ret_tok.type_ = Type::COMMA;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == '.') {
		cacheNextChar();

		ret_tok.type_ = Type::DOT;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == ':') {
		cacheNextChar();

		ret_tok.type_ = Type::COLON;
		ret_tok.value_ = buffer_;
	}
	else if (lastch_ == ';') {
		cacheNextChar();

		ret_tok.type_ = Type::SEMICOLON;
		ret_tok.value_ = buffer_;
	}
	return ret_tok;
}
