//
// Created by mateusz on 11.05.18.
//
#include <iostream>
#include <memory>
#include <sstream>

#include "../include/catch.hpp"
#include "Parser/Parser.h"

using  namespace Guarduaux;

TEST_CASE( "parser_tests" ) {

    SECTION("Funcion definitions"){
        std::string streamValue = " ";
        std::stringstream stream(streamValue);
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
        Parser parser(std::move(lexer));

        WHEN("Wrong function definition") {
            THEN("Exception appears - 1") {
                stream << "functio";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 2") {
                stream << "function 01";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 3") {
                stream << "function fun";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 4") {
                stream << "function fun dd";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 5") {
                stream << "function fun(";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 6") {
                stream << "function fun(01";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 7") {
                stream << "function fun()";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 8") {
                stream << "function fun()[";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 9") {
                stream << "function fun(){";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 10") {
                stream << "function fun(){}"
                          "11";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 10") {
                stream << "function fun(){}"
                          "function";
                REQUIRE_THROWS(parser.parse());
            }
        }


        WHEN("Correct function definition") {

            THEN("works - Contain main function") {
                stream << "func scene() {}";
                REQUIRE_NOTHROW(parser.parse());
            }
        }
    }

    SECTION("Init Statment parse"){
        std::string streamValue = " ";
        std::stringstream stream(streamValue);
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
        Parser parser(std::move(lexer));

        WHEN("Wrong init statement definition") {
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "zmienna"
                          "}";
                REQUIRE_THROWS(parser.parse());
            }


        }


        WHEN("Correct init statment definition") {

            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "zmienna ; "
                          "ab[2] ;"
                          "kol[zmienna]"
                          "}";

                //REQUIRE_NOTHROW(parser.parse());
            }
        }
    }


    SECTION("Assign  Statment parse"){
        std::string streamValue = " ";
        std::stringstream stream(streamValue);
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
        Parser parser(std::move(lexer));

        WHEN("Wrong assign statement definition") {
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "a;"
                          "zmienna = a"
                          "}";
                REQUIRE_THROWS(parser.parse());
            }


        }


        WHEN("Correct assign  statment definition") {

            THEN("works - Contain main function") {
                stream << "func rysuj(){}"
                          "func scene() {"
                          "a;"
                          "zmienna = a + 12 ;"
                          "kol[10];"
                          "kol[3] = zmienna ;"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }
            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "a;"
                          "zmienna = a + 12 * 8 ;"
                          "kol[10];"
                          "kol[3] = zmienna * a * 13 + 3;"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }

        }
    }


    SECTION("Loop  Statment parse"){
        std::string streamValue = " ";
        std::stringstream stream(streamValue);
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
        Parser parser(std::move(lexer));

        WHEN("Wrong Loop statement definition") {
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "for(a =1 ; a < 1 ; a = a + 1) {"
                          "}";
                REQUIRE_THROWS(parser.parse());
            }


        }


        WHEN("Correct assign  statment definition") {

            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "for(a = 1 ; a < 1 ; a = a + 1) {}"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }
            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "for_each kolekcja : iter {}"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }
        }
    }

    SECTION("Graph func  Statment parse"){
        std::string streamValue = " ";
        std::stringstream stream(streamValue);
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
        Parser parser(std::move(lexer));

        WHEN("Wrong graph functionstatement definition") {
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "kula draw cos;"

                          "}";
                REQUIRE_THROWS(parser.parse());
            }


        }


        WHEN("Correct graph function  statment definition") {

            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "kula move(1 , 2 , 3);"
                          "boks chngcol(255, 255, 0);"
                          "}";

                REQUIRE_NOTHROW(parser.parse());
            }
        }
    }

    SECTION("If  Statment parse"){
        std::string streamValue = " ";
        std::stringstream stream(streamValue);
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
        Parser parser(std::move(lexer));

        WHEN("Wrong if statement definition") {
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "if(1){"
                          "else{"
                          "}"
                          "}";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "if(){}"
                          "else{"
                          "}";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "if(){"
                          "else{"
                          "}"
                          "}";
                REQUIRE_THROWS(parser.parse());
            }


        }


        WHEN("Correct if  statment definition") {

            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "a;"
                          "if(a  < 3 ){}"
                          "else{"
                          "}"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }
            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "a;"
                          "if(a  < 3 || a < 1 ){}"
                          "else{"
                          "}"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }

            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "a;"
                          "b;"
                          "if(a  < 3 || a < 1 + b){}"
                          "else{"
                          "}"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }

            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "a;"
                          "if(a){}"
                          "else{"
                          "}"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }

            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "a;"
                          "b;"
                          "if(a * 8 < 3 || a < 1 + b){}"
                          "else{"
                          "}"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }
        }
    }

    SECTION("Return  Statment parse"){
        std::string streamValue = " ";
        std::stringstream stream(streamValue);
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
        Parser parser(std::move(lexer));

        WHEN("Wrong return statement definition") {
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "return"
                          "}";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "rrtur 2;"
                          "}";
                REQUIRE_THROWS(parser.parse());
            }
            THEN("Exception appears - 1") {
                stream << "func scene() {"
                          "if(){"
                          "else{"
                          "}"
                          "}";
                REQUIRE_THROWS(parser.parse());
            }


        }


        WHEN("Correct return  statment definition") {

            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "return 0;"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }
            THEN("works - Contain main function") {
                stream << "func scene() {"
                          "a =  2;"
                          "return a;"
                          "}";
                REQUIRE_NOTHROW(parser.parse());
            }

        }
    }

}

