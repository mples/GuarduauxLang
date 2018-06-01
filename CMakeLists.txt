cmake_minimum_required(VERSION 2.8)
project(Guarduaux_Lang)

set(CMAKE_CXX_STANDARD 17)


include_directories(src)

add_executable(Guarduaux_Lang
        include/catch.hpp
        tests/lexer_test.cpp
        tests/parser_tests.cpp
        src/Expresions/AndExpression.h
        src/Expresions/AssignableExpression.h
        src/Statements/AssignStatement.h
        src/Statements/BlockStatement.h
        src/Program/Exception.h
        src/Expresions/Expresion.h
        src/Statements/ForEachStatement.h
        src/Statements/ForStatement.h
        src/Statements/FuncCall.h
        src/Program/FuncDef.h
        src/Statements/GraphFunc.h
        src/Statements/IfStatement.h
        src/Lexer/Input.cpp
        src/Lexer/Input.h
        src/Lexer/Lexer.cpp
        src/Lexer/Lexer.h
        src/Expresions/LogicExpression.h
        #src/main.cpp
        src/Expresions/MultipExpression.h
        src/Parser/Parser.cpp
        src/Parser/Parser.h
        src/Statements/PeriodicFuncCall.h
        src/Program/Program.h
        src/Expresions/RelatExpression.h
        src/Program/Return.h
        src/Statements/ReturnStatement.h
        src/Expresions/SimpleAssnblExpression.h
        src/Expresions/SimpleLogicExpression.h
        src/Statements/Statement.h
        src/Token/Token.h
        src/Token/TokenType.h
        src/Token/TokenTypeTable.cpp
        src/Token/TokenTypeTable.h
        src/Program/Variable.cpp
        src/Program/Variable.h
        tests/program_test.cpp src/Program/Context.h)
