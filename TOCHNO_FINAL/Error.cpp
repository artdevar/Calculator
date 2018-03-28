#include "Error.h"

const char* ErrorMsg[] = { "Reading empty stack!",
	"Root of a negative number!",
	"log of 0 - (-)infinity!",
	"log of a negative number - indefined!", 
    "Operator is absent!",		
	"Operand is absent!",
	"No opening parenthesis!",
    "No closing parenthesis!",
    "Error type!",
	"Area of definition - arccos/arcsin: -1 <= X <= 1!",
	"Div by 0!",
	"Base of log must be greater than 0 & can't be equal 1!",
    "Value can't be equal 0!",
	"Base of root must be greater than 0!"
};


Error::Error(const int code) : ErrorCode(code) 
{}

const char * Error::what() const
{ 
	return ErrorMsg[ErrorCode]; 
}

int Error::whatNumber() const
{ 
	return ErrorCode; 
}