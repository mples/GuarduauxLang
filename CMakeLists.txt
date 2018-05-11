cmake_minimum_required(VERSION 3.10)
project(Guarduaux_Lang)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Guarduaux_Lang
        src/AddExpression.h
        src/AssignableExpression.h
        src/AssignStatement.h
        src/BlockStatement.h
        src/Exception.h
        src/Expresion.h
        src/ForEachStatement.h
        src/ForStatement.h
        src/FuncCall.h
        src/FuncDef.h
        src/GraphFunc.h
        src/IfStatement.h
        src/Input.cpp
        src/Input.h
        src/Lexer.cpp
        src/Lexer.h
        src/LogicExpression.h
        src/main.cpp
        src/MultipExpression.h
        src/Parser.cpp
        src/Parser.h
        src/PeriodicFuncCall.h
        src/Program.h
        src/RelatExpression.h
        src/Return.h
        src/SimpleAssnblExpression.h
        src/SimpleLogicExpression.h
        src/Statement.h
        src/Token.h
        src/TokenType.h
        src/TokenTypeTable.cpp
        src/TokenTypeTable.h
        src/Variable.cpp
        src/Variable.h)
