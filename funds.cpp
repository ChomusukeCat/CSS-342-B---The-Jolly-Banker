#include "funds.h"

Funds::Funds(string fund_name)
{
	fund_name_ = fund_name;
}

Funds::~Funds()
{

}

int Funds::get_balance() const
{
	return balance_;
}

string Funds::get_fund_name() const
{
	return fund_name_;
}

bool Funds::Deposit(int n)
{
	balance_ += n;
	return true;
}

bool Funds::Withdraw(int n)
{
	balance_ -= n;
	return true;
}
