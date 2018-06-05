#pragma once

#include <ostream>

namespace Guarduaux {
	enum class TokenType {
		FUNC, RET,

		CUR_BR_OP, CUR_BR_CL,
		SQR_BR_OP, SQR_BR_CL,
		RND_BR_OP, RND_BR_CL,

		PERIODIC_OP,

		MUL_OP,
		DIV_OP,

		ADD_OP,
		SUB_OP,

		GOE_OP,
		GTH_OP,
		LOE_OP,
		LTH_OP,


		EQU_OP,
		NEQ_OP,

		AND_OP, OR_OP,

		NEG,

		ASN,

		IF, ELSE,

		FOR,

		DRAW, SCALE, MOVE, CHNGCOL,
		BOX, CYLINDER,
		POS, COL, DIM,

		IDENTIFIER,
		NUMBER,
		MINUS,
		DOT,
		COMMA,
		COLON,
		SEMICOLON,

		END_OF_FILE,
		UNIDENTIFIED
	};
	inline std::ostream &operator<<(std::ostream &os, const TokenType &type) {
		//os << "type";
		return os;
	}
}
