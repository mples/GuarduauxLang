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

        WHEN("No scene func defined ") {
            THEN("Exception appears") {
                stream << "func sceneee(){}";
                Program progr = parser.parse();
                REQUIRE_THROWS(progr.generateScene());
            }

        }


        WHEN("Correct scane function definition") {

            THEN("works - Contain scene function") {
                stream << "func scene() {}";
                Program progr = parser.parse();
                REQUIRE_NOTHROW(progr.generateScene());
            }
        }

        WHEN("Program contains multiple function") {

            THEN("scene func is found and run") {
                stream << "func tkom() {}"
                          "func scene() {}";
                Program progr = parser.parse();
                REQUIRE_NOTHROW(progr.generateScene());
            }
        }

        WHEN("Program contains multiple function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "return 1+1 * 2;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 3 );
            }
        }

        WHEN("Program contains multiple function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "return 1 + 1 / 0;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE_THROWS(progr.generateScene().variable_->get() == 1 );
            }
        }

        WHEN("Program contains multiple function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "return 8 / 1+1;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 9 );
            }
        }

        WHEN("Program contains multiple function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "return 1+1 && 1-1;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 0 );
            }
        }

        WHEN("Program contains multiple function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "return 2+1 && 3-4;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 1 );
            }
        }

        WHEN("Program contains multiple function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "return 1+1 || 1-1;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 1 );
            }
        }

        WHEN("Program contains multiple function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "return 0 || 1-1;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 0 );
            }
        }
        WHEN("Program contains multiple function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "a = 3;"
                          "b = 6;"
                          "return a > b;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 0 );
            }
        }

        WHEN("Program contains if function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "a = 3;"
                          "b = 6;"
                          "if(a > b){"
                          "return 2;"
                          "}"
                          "else { return 1;}"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 1 );
            }
        }

        WHEN("Program contains if function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "a = 5;"
                          "b = 3;"
                          "if(b <= a){"
                          "c=2; d = 6;"
                          "return c+d;"
                          "}"
                          "else { return 6;}"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 8 );
            }
        }

        WHEN("Program contains if function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "a = 4;"
                          "b = 2;"
                          "if(b >= a){"
                          "c=2; d = 6;"
                          "return c+d;"
                          "}"
                          "else { return 6;}"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 6 );
            }
        }

        WHEN("Program contains if function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "a = 10;"
                          "b = 3;"
                          "if(b < a){"
                          "c=2; d = 6;"
                          "return c+d;"
                          "}"
                          "else { return 6;}"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 8 );
            }
        }

        WHEN("For function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "a = 10;"
                          "b = 3;"
                          "for(a=1 ; a < 4; a = a+1){"
                          "b = b + 2; } "
                          "return b;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 9 );
            }
        }


        WHEN("Calling other function than scene") {

            THEN("func is found") {
                stream << "func tkom(a) {"
                          "return a+5;"
                          "}"
                          "func scene() {"
                          "a = 10;"
                          "b = tkom(a);"
                          "return b;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                Return result = progr.generateScene();
                REQUIRE(result.variable_->get() == 15 );
            }
        }

        WHEN("Calling other function than scene") {

            THEN("func is found") {
                stream << "func tkom(a) {"
                          "return a+5;"
                          "}"
                          "func scene() {"
                          "a=2;"
                          "tkom(a)~(2);"
                          "boks draw box pos(50,2,1) col(0,0,1) dim(1,1,1);"
                          "cyl draw cylinder pos(0,0,1) col(1,1,0) dim(123,43,15);"
                          "return a;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                Return result = progr.generateScene();
                REQUIRE(result.variable_->get() == 2 );
            }
        }

        WHEN("Calling other function than scene") {

            THEN("func is found") {
                stream << "func tkom(a) {"
                          "return a+5;"
                          "}"
                          "func scene() {"
                          "a=2;"
                          "tkom(a)~(2);"
                          "boks draw box pos(50,2,60) col(0,100,0) dim(100,100,100);"
                          "cyl draw cylinder pos(50,0,1) col(1,1,0) dim(123,43,15);"
                          "cyl move (1,1,1);"
                          "boks scale(5,1,1);"
                          "return a;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                Return result = progr.generateScene();
                REQUIRE(result.variable_->get() == 2 );
                //progr.render();
            }
        }

        WHEN("Program contains if function") {

            THEN("func is found") {
                stream << "func tkom() {}"
                          "func scene() {"
                          "b;"
                          "a[10];"
                          "a[2] = 3;"
                          "b = a[2];"
                          "return b;"
                          "}";
                Program progr = parser.parse();
                REQUIRE(progr.isVaildFunc("tkom"));
                REQUIRE(progr.generateScene().variable_->get() == 3 );
            }
        }


    }

}