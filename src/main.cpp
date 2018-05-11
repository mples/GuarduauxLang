//
// Created by mateusz on 11.05.18.
//

#include <iostream>
#include <sstream>
#include "Parser.h"


using namespace Guarduaux;

int main() {
    std::cout << "Hello Guarduaux" << std::endl;

    std::string streamValue = " ";
    std::stringstream stream(streamValue);
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(stream);
    Parser parser(std::move(lexer));

    stream << " a = a;";

    parser.parse();

}