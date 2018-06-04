//
// Created by mateusz on 11.05.18.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "Parser/Parser.h"
#include "Program/Program.h"


using namespace Guarduaux;

int main(int argc, char** argv) {

    Parser parser;
    Program prog;
    std::fstream file;

    if(argc == 2) {
        file.open(argv[1], std::ios::in);
        if(!file.good()) {
            std::cout << "file not found\n";
            return -1;
        }
        try {
            parser.setLexer(std::make_unique<Lexer>(file));
            prog = parser.parse();
            prog.generateScene();
            prog.render();

        } catch (Exception &e) {
            //std::cout << e.what() << std::endl;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        file.close();
    } else {
        std:: cout << "Put file path in argument\n";
    }

    return 0;

}