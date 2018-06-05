#include "TokenTypeTable.h"

const  std::string Guarduaux::TokenTypeTable::getName(const TokenType & type)
{
	const static std::unordered_map<TokenType,std::string> typeNamesTable = {
		{TokenType::FUNC,	"Function"},
		{TokenType::RET,	"Return"},

		{TokenType::CUR_BR_OP, "Open curly bracket" },
		{TokenType::CUR_BR_CL, "Close curly bracket"},
		{ TokenType::SQR_BR_OP,	"Open square bracket" },
		{ TokenType::SQR_BR_CL,	"Close square bracket" },
		{ TokenType::RND_BR_OP,	"Open round bracket" },
		{ TokenType::RND_BR_CL,	"Open round bracket" },

		{ TokenType::PERIODIC_OP,	"Periodic operator" },
	
		{ TokenType::MUL_OP,	"Multipilcation operator" },
		{ TokenType::DIV_OP,	"Division operator" },
			
		{ TokenType::ADD_OP,	"Add operator" },
		{ TokenType::SUB_OP,	"Subract operator" },

		{ TokenType::GOE_OP,	"Greather or equal operator" },
		{ TokenType::GTH_OP,	"Greather then operator" },
		{ TokenType::LOE_OP,	"Less or equal operator" },
		{ TokenType::LTH_OP,	"Less then operator" },


		{ TokenType::EQU_OP,	"Equal operator" },
		{ TokenType::NEQ_OP,	"Not equal operaotr" },

		{ TokenType::AND_OP,	"And operaotr" },
		{ TokenType::OR_OP,		"Or opearotr" },

		{ TokenType::NEG,		"Negation operaotr" },

		{ TokenType::ASN,		"Assingment operator" },

		{ TokenType::IF,		"If keyword" },
		{ TokenType::ELSE,		"Else keyword" },

		{ TokenType::FOR,		"For keyword" },

		{ TokenType::DRAW,		"draw keyword" },
		{ TokenType::SCALE,		"scale keyword" },
		{ TokenType::MOVE,		"move keyword"  },
		{ TokenType::CHNGCOL,	"chngcol keyword" },
		{ TokenType::BOX,		"box keyword" },
		{ TokenType::CYLINDER,	"cylinder keyword" },
		{ TokenType::POS,		"pos keyword" },
		{ TokenType::COL,		"col keyword" },
		{ TokenType::DIM,		"dim keyword" },

		{ TokenType::IDENTIFIER,	"Identifier" },
		{ TokenType::NUMBER,		"Number" },
		{ TokenType::MINUS,			"Minus" },
		{ TokenType::DOT,			"Dot" },
		{ TokenType::COMMA,			"Comma" },
		{ TokenType::COLON,			"Colon" },
		{ TokenType::SEMICOLON,		"Semicolon" },

		{ TokenType::END_OF_FILE,		"End of file" },
		{ TokenType::UNIDENTIFIED,		"Unidentified" }
	};

	return typeNamesTable.at(type);
}
