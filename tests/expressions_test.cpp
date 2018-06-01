//
// Created by mateusz on 01.06.18.
//

#include <iostream>
#include <memory>
#include <sstream>

#include "../include/catch.hpp"
#include "Parser/Parser.h"

using  namespace Guarduaux;

TEST_CASE( "expressions_tests" ) {
    SECTION("parsing expressions "){

        std::string streamValue = " ";
        std::stringstream stream(streamValue);
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
        Parser parser(std::move(lexer));




        WHEN("Correct scane function definition") {

            THEN("works - Contain scene function") {
                stream << "func scene() {"
                          "a ;"
                          "}";
                Program progr = parser.parse();
                REQUIRE_NOTHROW(progr.run());
            }
        }


    }

}