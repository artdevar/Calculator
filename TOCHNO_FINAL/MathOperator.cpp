#include "MathOperator.h"
#include <math.h>

MathOperator::MathOperator(const string & str) : operation(str)
{
	if (operation == "+" || operation == "-")
	{
		inputRank = 1;
		stackRank = 1;
	}
	else if (operation == "*" || operation == "/" || operation == "^" || operation == "%" || operation == ":")
	{
		inputRank = 2;
		stackRank = 2;
	}
	else if (operation == "(")
	{
		inputRank = 4;
		stackRank = -1;	
	}
	else if (operation == ")")
	{
		inputRank = 0;
		stackRank = 0;
	}
	else
	{
		inputRank = 3;
		stackRank = 3;
	}
}

bool MathOperator::operator >= (const MathOperator & obj) const
{
	return stackRank >= obj.inputRank; 
}


void MathOperator::Evaluate(Stack<long double> & stack)
{
	float operand1 = stack.Pop();
	if (operation == "+" || operation == "-"   || operation == "*"   || operation == "/" || operation == "^" || operation == "%" || 
		operation == ":" || operation == "log" || operation == "mod" || operation == "root" )
	{
		float operand2 = stack.Pop();
		if (operation == "+") stack.Push(operand2 + operand1);
		else if (operation == "-") stack.Push(operand2 - operand1);
		else if (operation == "*") stack.Push(operand2 * operand1);
		else if (operation == "/" || operation == ":")
		{	
			if (operand1 == 0)
			{
				throw Error(div_zero);
			}
			else
			{
				stack.Push(operand2 / operand1);
			}
		}
		else if (operation == "%") stack.Push(operand2*operand1 / 100);
		else if (operation == "^") stack.Push(pow(operand2, operand1));
		else if (operation == "log")
		{
			if (operand2 <= 0 || operand2 == 1)
			{
				throw Error(log_a);
			}
			if (operand1 == 0)
			{
				throw Error(log0);
			}
			else if (operand1 < 0)
			{
				throw Error(negate_log);
			}
			stack.Push(log10(operand1) / log10(operand2));
		}
		else if (operation == "mod")
		{
			if ((int)operand1 == 0)
			{
				throw Error(value_null);
			}
			stack.Push((int)operand2 % (int)operand1);
		}
		else if (operation == "root")
		{
			if (operand1 < 0)
			{
				throw Error(negate_sqrt);
			}
			else if (operand2 == 0 || operand2 < 0)
			{
				throw Error(negate_n);
			}
			else
			{
				stack.Push(pow(operand1, 1 / operand2));
			}
		}
	}
	else
	{
		const double PI(3.1415926535);
		if (operation == "negate") stack.Push(-operand1);
		else if (operation == "e" || operation == "exp") stack.Push(exp(operand1));
		else if (operation == "arccos")
		{
			if (operand1 < -1 || operand1 > 1)
			{
				throw Error(domain);
			}
			else
			{
				stack.Push(acos(operand1) * 180 / PI);
			}
		}
		else if (operation == "arcsin")
		{
			if (operand1 < -1 || operand1 > 1)
			{
				throw Error(domain);
			}
			else
			{
				stack.Push(asin(operand1) * 180 / PI);
			}
		}
		else if (operation == "arctg") stack.Push(atan(operand1)*180/PI);
		else if (operation == "sqrt")
		{
			if (operand1 < 0)
			{
				throw Error(negate_sqrt);
			}
			else
			{
				stack.Push(sqrt(operand1));
			}
		}
		else if (operation == "cbrt")
		{
			if (operand1 < 0)
			{
				throw Error(negate_sqrt);
			}
			else
			{
				stack.Push(cbrt(operand1));
			}
		}
		else if (operation == "sin")
		{
			operand1 = operand1 * PI / 180;
			stack.Push(sin(operand1));
		}
		else if (operation == "cos")
		{
			operand1 = operand1 * PI / 180;
			stack.Push(cos(operand1));
		}
		else if (operation == "ln")
		{
			if (operand1 == 0)
			{
				throw Error(log0);
			}
			else if (operand1 < 0)
			{
				throw Error(negate_log);
			}
			else
			{
				stack.Push(log(operand1));
			}
		}
		else if (operation == "tg")
		{
			operand1 = operand1 * PI / 180;
			stack.Push(tan(operand1));
		}
		else if (operation == "sh") stack.Push(sinh(operand1)*180/PI);
		else if (operation == "ch") stack.Push(cosh(operand1)*180/PI);
		else if (operation == "th") stack.Push(tanh(operand1)*180/PI);
		else if (operation == "lg")
		{
			if (operand1 == 0)
			{
				throw Error(log0);
			}
			else if (operand1 < 0)
			{
				throw Error(negate_log);
			}
			else
			{
				stack.Push(log10(operand1));
			}
		}
	}
}

string MathOperator::get_operator() const
{ 
	return operation; 
}