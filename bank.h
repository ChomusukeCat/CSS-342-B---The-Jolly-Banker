/*	
*	Bank class 
*	Handles transactions and processes queue
*/
#ifndef BANK_H
#define BANK_H
#include "account.h"
#include "bstree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;
class Bank
{
public:
	Bank();
	~Bank();
	bool Open(string first_name, string last_name, int id);
	bool Deposit(int id, int fund_id, int amount);
	bool Withdraw(int id, int fund_id, int amount);
	bool History(int id, int fund_id);
	bool Transfer(int src_id,int dest_fund_id, int amount, int src_fund_id, int dest_id);
	bool Enqueue(vector<string> transaction);
	bool ProcessQueue();
	void Display() const;
private:
	BSTree accounts_tree_;
	queue<vector<string>> transaction_queue_;
};
#endif
