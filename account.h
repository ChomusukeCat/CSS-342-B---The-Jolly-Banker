/*
*	Account class
*	Handles transaction functions
*	Stores history and funds
*/
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "funds.h"
#include "transaction.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Account
{
public:
	Account(string first, string last, int id);
	~Account();

	bool Deposit(int fund_id, int amount);
	bool Withdraw(int fund_id, int amount);
	bool TDeposit(int src_acc_id, int src_fund_id, int amount, int dest_acc_id, int dest_fund_id);
	bool TWithdraw(int src_acc_id, int src_fund_id, int amount, int dest_acc_id, int dest_fund_id);
	void ShowHistory(int fund_id) const;
	int get_id() const;
	string get_name() const;
	int get_funds(int fund_id) const;

	bool operator==(const Account& other) const;
	bool operator<(const Account& other) const;
	friend ostream& operator<<(ostream& out_stream, const Account& acc);
private:
	int acc_id_ = -1000;
	string first_name_ = "";
	string last_name_ = "";
	Transaction* history_[10];
	Funds* funds_[10];

	bool JointFundWithdraw(int fund_id, int amount);
};

#endif // !Account
