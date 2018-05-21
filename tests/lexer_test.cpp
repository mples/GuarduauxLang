//
// Created by mateusz on 11.05.18.
//
#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../src/Lexer.h"




TEST_CASE( "input_tests"){

    SECTION("text_is_read") {
        std::istringstream iss("abc");
        Input input(iss);

        REQUIRE(input.getNextChar() == 'a');
        REQUIRE(input.getNextChar() == 'b');
        REQUIRE(input.getNextChar() == 'c');
    }
}



TEST_CASE("lexer_tests"){
    SECTION("identifiers_are_scanned")
    {
        using Type = Guarduaux::TokenType;

        using namespace Guarduaux;

        std::istringstream iss;
        Token token = Token::unidentifiedType();
        Lexer lexer(iss);

        iss.str("ident ident_  _id_ id1_{}");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::IDENTIFIER);
        REQUIRE(token.value_ == "ident");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::IDENTIFIER);
        REQUIRE(token.value_ == "ident_");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::IDENTIFIER);
        REQUIRE(token.value_ == "_id_");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::IDENTIFIER);
        REQUIRE(token.value_ == "id1_");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::CUR_BR_OP);
        REQUIRE(token.value_ == "{");
        token = lexer.getToken();
        REQUIRE(token.type_ == Type::CUR_BR_CL);
        REQUIRE(token.value_ == "}");

    }

    SECTION("numbers_are_scanned")
    {
        using Type = Guarduaux::TokenType;
        using namespace Guarduaux;

        std::istringstream iss;
        Token token = Token::unidentifiedType();
        Lexer lexer(iss);

        iss.str("113 234 3 4 0 0 4 66 34 003   00007");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "113");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "234");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "3");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "4");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "0");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "0");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "4");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "66");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "34");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "003");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NUMBER);
        REQUIRE(token.value_ == "00007");
    }

    SECTION("keywords_are_scanned")
    {
        using Type = Guarduaux::TokenType;
        using namespace Guarduaux;

        std::istringstream iss;
        Token token = Token::unidentifiedType();
        Lexer lexer(iss);

        iss.str("draw box pos dim col scale sphere chngcol move");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::DRAW);
        REQUIRE(token.value_ == "draw");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::BOX);
        REQUIRE(token.value_ == "box");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::POS);
        REQUIRE(token.value_ == "pos");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::DIM);
        REQUIRE(token.value_ == "dim");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::COL);
        REQUIRE(token.value_ == "col");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::SCALE);
        REQUIRE(token.value_ == "scale");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::SPHERE);
        REQUIRE(token.value_ == "sphere");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::CHNGCOL);
        REQUIRE(token.value_ == "chngcol");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::MOVE);
        REQUIRE(token.value_ == "move");

    }

    SECTION("operators_are_scanned")
    {
        using Type = Guarduaux::TokenType;
        using namespace Guarduaux;

        std::istringstream iss;
        Token token = Token::unidentifiedType();
        Lexer lexer(iss);

        iss.str("!= == >= > < <= = !   ~  ||  &&  +  -  *  /");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NEQ_OP);
        REQUIRE(token.value_ == "!=");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::EQU_OP);
        REQUIRE(token.value_ == "==");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::GOE_OP);
        REQUIRE(token.value_ == ">=");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::GTH_OP);
        REQUIRE(token.value_ == ">");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::LTH_OP);
        REQUIRE(token.value_ == "<");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::LOE_OP);
        REQUIRE(token.value_ == "<=");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::ASN);
        REQUIRE(token.value_ == "=");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::NEG);
        REQUIRE(token.value_ == "!");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::PERIODIC_OP);
        REQUIRE(token.value_ == "~");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::OR_OP);
        REQUIRE(token.value_ == "||");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::AND_OP);
        REQUIRE(token.value_ == "&&");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::ADD_OP);
        REQUIRE(token.value_ == "+");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::SUB_OP);
        REQUIRE(token.value_ == "-");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::MUL_OP);
        REQUIRE(token.value_ == "*");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::DIV_OP);
        REQUIRE(token.value_ == "/");

    }

    SECTION("special_sings_are_scanned")
    {
        using Type = Guarduaux::TokenType;
        using namespace Guarduaux;

        std::istringstream iss;
        Token token = Token::unidentifiedType();
        Lexer lexer(iss);

        iss.str("{} [] () ; : , . ");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::CUR_BR_OP);
        REQUIRE(token.value_ == "{");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::CUR_BR_CL);
        REQUIRE(token.value_ == "}");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::SQR_BR_OP);
        REQUIRE(token.value_ == "[");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::SQR_BR_CL);
        REQUIRE(token.value_ == "]");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::RND_BR_OP);
        REQUIRE(token.value_ == "(");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::RND_BR_CL);
        REQUIRE(token.value_ == ")");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::SEMICOLON);
        REQUIRE(token.value_ == ";");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::COLON);
        REQUIRE(token.value_ == ":");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::COMMA);
        REQUIRE(token.value_ == ",");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::DOT);
        REQUIRE(token.value_ == ".");


    }

    SECTION("invalid_signs_are_scanned")
    {
        using Type = Guarduaux::TokenType;
        using namespace Guarduaux;

        std::istringstream iss;
        Token token = Token::unidentifiedType();
        Lexer lexer(iss);

        iss.str("@ # &  \\ ");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::UNIDENTIFIED);
        REQUIRE(token.value_ == "@");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::UNIDENTIFIED);
        REQUIRE(token.value_ == "#");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::UNIDENTIFIED);
        REQUIRE(token.value_ == "&");

        token = lexer.getToken();
        REQUIRE(token.type_ == Type::UNIDENTIFIED);
        REQUIRE(token.value_ == "\\");

    }

    SECTION("exception_is_thrown_when_identifier_too_long")
    {
        using namespace Guarduaux;

        std::istringstream iss;

        Lexer lexer(iss);

        std::string str(IDENTIFIER_MAX_LENGTH + 1, 'g');
        iss.str(str);

        REQUIRE_THROWS_AS(lexer.getToken(), std::runtime_error);

    }

    SECTION("file_position_is_tracked")
    {
        using namespace Guarduaux;

        std::istringstream iss;
        Token token = Token::unidentifiedType();

        Lexer lexer(iss);

        iss.str("1234  \n"
                "ala ma kota;");

        token = lexer.getToken();
        REQUIRE(token.pos_.line_ == 1);
        REQUIRE(token.pos_.column_ == 0);

        token = lexer.getToken();
        REQUIRE(token.pos_.line_ == 2);
        REQUIRE(token.pos_.column_ == 0);

        token = lexer.getToken();
        REQUIRE(token.pos_.line_ == 2);
        REQUIRE(token.pos_.column_ == 4);

        token = lexer.getToken();
        REQUIRE(token.pos_.line_ == 2);
        REQUIRE(token.pos_.column_ == 7);

    }

}




