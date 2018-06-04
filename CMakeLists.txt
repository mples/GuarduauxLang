cmake_minimum_required(VERSION 2.8)
project(Guarduaux_Lang)

set(CMAKE_CXX_STANDARD 17)


include_directories(src)

add_executable(Guarduaux_Lang
        include/catch.hpp
        #tests/lexer_test.cpp
        #tests/parser_tests.cpp
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
        src/main.cpp
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
        #tests/program_test.cpp
        src/Program/Context.h
        #tests/expressions_test.cpp
        src/Expresions/MultipExpression.cpp
        src/Program/Context.cpp src/Statements/DrawGraphicFunc.h src/Statements/ScaleGraphFunc.h src/Statements/MoveGraphFunc.h src/Statements/ChngcolGraphFunc.h src/Program/GraphicContext.cpp src/Program/GraphicContext.h src/Graphic/GraphicObject.h src/Graphic/Box.cpp src/Graphic/Box.h src/Graphic/Cylinder.cpp src/Graphic/Cylinder.h src/Program/Program.cpp src/Graphic/Shader.cpp src/Graphic/Shader.h)


# Source files

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Executable definition and properties
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

#glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
