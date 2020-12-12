#include "transaction.h"

Transaction::Transaction(string fund_name)
{
	fund_name_ = fund_name;
}

Transaction::~Transaction()
{
}

bool Transaction::Record(string transaction)
{
	history_.push_back(transaction);
	return true;
}

vector<string> Transaction::get_history()
{
	return history_;
}
