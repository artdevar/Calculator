enum Error_Codes 
{
	empty_st, negate_sqrt, log0, negate_log, absent_operator, absent_operand,
	bkt_l, bkt_r, type_error, domain, div_zero, log_a, value_null, negate_n
};

class Error
{
public:
	Error() = default;
	Error(const int);
	const char* what() const;
	int whatNumber() const;
private:
	int ErrorCode{ -1 };
};