#include "Stack.h"
#include <string>
using std::string;

class MathOperator
{
public:
	MathOperator() = default;
	MathOperator(const string &);
	bool operator >= (const MathOperator &) const;
	void Evaluate(Stack<long double> &);
	string get_operator() const;
private:
	string operation{};
	int inputRank{};
	int stackRank{};
}; 