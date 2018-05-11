#include "Input.h"


char Input::currentChar() const
{
	return current_;
}

char Input::getNextChar()
{
	return current_ = static_cast<char>(in_.get());
}

char Input::peekNextChar()
{
	return in_.peek();
}

Input::Input(std::istream& in) : in_(in), current_('\0')
{
}


Input::~Input()
{
}

