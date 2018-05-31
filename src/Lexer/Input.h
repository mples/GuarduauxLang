#pragma once
#include <iostream>

class Input
{
public:
	char currentChar() const;
	char getNextChar();
	char peekNextChar();
	const bool isEndOfFile();

	Input(std::istream& in);
	~Input();
private:
	std::istream& in_;
	char current_;
};


