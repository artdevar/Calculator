#include "MathOperator.h"

#include <iostream>
#include <cctype>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

inline void Hello() 
{
	cout << "\t\t<<Calculator>>" << endl;
	cout << "\n||FAQ: negate6 = -6, 3root27 = 3, 2log8 = 3, sin, arccos etc." << endl;
	cout << "||clear - clear of console." << endl;
	cout << "||exit & quit - close console." << endl;
	cout << "\n\tEnter the expression. For solution - press \"ENTER\"." << endl << endl;
}

bool isOperator(const char & op)
{
		switch (op)
		{
			case '+':
			case '-':
			case '/':
			case '*':
			case '(':
			case ':':
			case '%':
			case '^':
				return true;
				break;
			default: 
				return false;
		}
}

bool isUnary(const string & str) 
{
	if (str == "negate" || str == "arcsin" || str == "cos"   || str == "tg"   ||
		str == "arccos" || str == "sin"    || str == "arctg" || str == "sqrt" ||
		str == "ln"     || str == "lg"     || str == "e"     || str == "exp"  ||
		str == "cbrt"   || str == "sh"     || str == "ch"    || str == "th"   ||
		str == "log"    || str == "mod"    || str == "root")
	{
		return true;
	}
	else
	{
		throw Error(type_error);
	}
}


int main()
{
	Hello();
	while (true)
	{
		Stack<MathOperator> Operators{};
		Stack<long double> Operands{};
		MathOperator obj1{}, obj2{};
		int rank{};
		long double number{};
		char symb{};
		cout << "> ";
		while (cin.get(symb) && symb != '\n')
		{
			string str{};
			if (isdigit(symb))
			{
				cin.putback(symb);
				cin >> number;
				try
				{
					if (rank > 1)
					{
						throw Error(absent_operator);
					}
				}
				catch (Error & e)
				{
					cerr << "Error #" << e.whatNumber() + 1 << ": " << e.what() << endl << endl;
					rank = 404;
					break;
				}
				rank++;
				Operands.Push(number);
			}
			else if (isalpha(symb))
			{
				char TERM[8];
				int i{};
				do
				{
					TERM[i] = symb;
					i++;
				} while (cin.get(symb) && isalpha(symb));
				TERM[i] = 0x00;
				str = TERM;
				if (str == "log" || str == "mod" || str == "root")
				{
					rank--;
				}
				else if (str == "clear" || str == "CLEAR")
				{
					system("cls");
					rank = 404;
					break;
				}  
				else if (str == "exit" || str == "quit" || str == "EXIT" || str == "QUIT")
				{
					return 0;
				}
				try
				{
					if (rank < 0)
					{
						throw Error(absent_operand);
					}
					if (isUnary(str))
					{
						obj1 = MathOperator(str);
						Operators.Push(obj1);
					}
				}
				catch (Error & e)
				{
					cerr << "Error #" << e.whatNumber() + 1 << ": " << e.what() << endl << endl;
					rank = 404;
					break;
				}
				cin.putback(symb);
			}
			else if (isOperator(symb))
			{
				if (symb != '(')
				{
					rank--;
				}
				try
				{
					if (rank < 0)
					{
						throw Error(absent_operand);
					}
				}
				catch (Error & e)
				{
					cerr << "Error #" << e.whatNumber() + 1 << ": " << e.what() << endl << endl;
					rank = 404;
					break;
				}
				str = symb;
				obj1 = MathOperator(str);
				while (!Operators.StackEmpty() && (obj2 = Operators.Peek()) >= obj1)
				{
					obj2 = Operators.Pop();
					obj2.Evaluate(Operands);
				}
				Operators.Push(obj1);
			}
			else if (symb == ')')
			{
				str = symb;
				obj1 = MathOperator(str);
				try
				{
					if (rank == 0)
					{
						throw Error(absent_operand);
					}
				}
				catch (Error & e)
				{
					cerr << "Error #" << e.whatNumber() + 1 << ": " << e.what() << endl << endl;
					rank = 404;
					break;
				}
				while (!Operators.StackEmpty() && (obj2 = Operators.Peek()) >= obj1)
				{
					obj2 = Operators.Pop();
					obj2.Evaluate(Operands);
				}
				try
				{
					if (Operators.StackEmpty())
					{
						throw Error(bkt_l);
					}
				}
				catch (Error & e)
				{
					cerr << "Error #" << e.whatNumber() + 1 << ": " << e.what() << endl << endl;
					rank = 404;
					break;
				}
				obj2 = Operators.Pop();
			}
		}

		if (rank == 404)
		{
			cin.ignore(cin.rdbuf()->in_avail());
			continue;
		}

		try
		{
			if (rank > 1)
			{
				throw Error(absent_operator);
			}
			else if (rank < 1)
			{
				throw Error(absent_operand);
			}
			while (!Operators.StackEmpty())
			{
				obj1 = Operators.Pop();
				if (obj1.get_operator() == "(")
				{
					throw Error(bkt_r);
				}
				obj1.Evaluate(Operands);
			}
			if (!Operands.StackEmpty())
			{
				cout << "\t< Answer: " << round(Operands.Pop() * 1000) / 1000 << " >" << endl << endl;
			}
		}
		catch (Error & e)
		{
			cerr << "Error #" << e.whatNumber() + 1 << ": " << e.what() << endl << endl;
		}
		cin.ignore(cin.rdbuf()->in_avail()); // очистка буфера 
	}
}