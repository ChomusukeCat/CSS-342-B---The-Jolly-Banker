/*	
*	Funds class
*	Handles balances of funds
*/
#ifndef FUNDS_H
#define FUNDS_H
#include <vector>
#include <string>
using namespace std;
class Funds
{
public:
	Funds(string fund_name);
	~Funds();
	
	bool Deposit(int n);
	bool Withdraw(int n);
	int get_balance() const;
	string get_fund_name() const;
private:
	int balance_ = 0;
	string fund_name_ = "";
};
#endif
