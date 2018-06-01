//
// Created by mateusz on 31.05.18.
//

#include <iostream>
#include <memory>
#include <sstream>

#include "../include/catch.hpp"
#include "Parser/Parser.h"

using  namespace Guarduaux;

TEST_CASE( "function_tests" ) {
    SECTION("Running program "){

        std::string streamValue = " ";
        std::stringstream stream(streamValue);
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
        Parser parser(std::move(lexer));
/*
        WHEN("No scene func defined ") {
            THEN("Exception appears") {
                stream << "func sceneee(){}";
                Program progr = parser.parse();
                REQUIRE_THROWS(progr.run());
            }

        }


        WHEN("Correct scane function definition") {

            THEN("works - Contain scene function") {
                stream << "func scene() {}";
                Program progr = parser.parse();
                REQUIRE_NOTHROW(progr.run());
            }
        }

        WHEN("Program contains multiple function") {

            THEN("scene func is found and run") {
                stream << "func tkom() {}"
                          "func scene() {}";
                Program progr = parser.parse();
                REQUIRE_NOTHROW(progr.run());
            }
        }*/

        WHEN("Program contains multiple function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "return 2;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.run().variable_->get() == 2);
            }
        }
    }

}