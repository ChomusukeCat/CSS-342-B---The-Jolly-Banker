/*	
*	CSS 342 B Program 5: Bank
*	Steven Chau
*	Transaction class
*	Handles and stores history of transactions
*	
*/
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Transaction
{
public:
	Transaction(string fund_name);
	~Transaction();

	bool Record(string transaction);
	vector<string> get_history();
private:
	string fund_name_;
	vector<string> history_;
};
#endif // !TRANSACTION_H
