/*	
*	CSS 342 B Program 5: Bank
*	Steven Chau
*	Driver code for bank program
*	Reads file and starts transaction process
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include<fstream>
#include "bank.h"
using namespace std;

int main()
{
	Bank* bank = new Bank();
	vector<string> transaction_list;
	ifstream in("BankTransIn.txt");
	string read_line;
	if (!in)
	{
		cerr << "ERROR: Cannot open file" << endl;
	}
	/*
	*	For each line in the file,
	*	split that line into appropriate parts-
	*	depending on transaction type.
	*	Push those parts into vector then add-
	*	the vector into queue and clear the vector-
	*	to repeat the process until all lines- 
	*	have been read.
	*/
	while (!in.eof())
	{
		getline(in, read_line);
		if (read_line.empty())
		{
			break;
		}
		istringstream parse_line(read_line);
		string transaction_type;
		parse_line >> transaction_type;
				
		if (transaction_type == "O")
		{
			string last_name, first_name, acc_id;
			parse_line >> first_name >> last_name >> acc_id;

			transaction_list.push_back(transaction_type);
			transaction_list.push_back(first_name);
			transaction_list.push_back(last_name);
			transaction_list.push_back(acc_id);
		}
		else if (transaction_type == "W" || transaction_type == "D")
		{
			transaction_list.push_back(transaction_type);
			int acc_id, fund_id, amount;
			parse_line >> acc_id >> amount;
			fund_id = acc_id % 10;
			acc_id = acc_id / 10;

			transaction_list.push_back(to_string(acc_id));
			transaction_list.push_back(to_string(fund_id));
			transaction_list.push_back(to_string(amount));
		}
		else if (transaction_type == "T")
		{
			transaction_list.push_back(transaction_type);
			int src_acc_id, src_fund_id, amount, dest_acc_id, dest_fund_id;
			parse_line >> src_acc_id >> amount >> dest_acc_id;
			src_fund_id = src_acc_id % 10;
			src_acc_id = src_acc_id / 10;
			dest_fund_id = dest_acc_id % 10;
			dest_acc_id = dest_acc_id / 10;

			transaction_list.push_back(to_string(src_acc_id));
			transaction_list.push_back(to_string(src_fund_id));
			transaction_list.push_back(to_string(amount));
			transaction_list.push_back(to_string(dest_acc_id));
			transaction_list.push_back(to_string(dest_fund_id));
		}
		else if (transaction_type == "H")
		{
			transaction_list.push_back(transaction_type);
			string acc_id;
			parse_line >> acc_id;

			transaction_list.push_back(acc_id);
		}
		else
		{
			cerr << "ERROR: Invalid transaction type" << endl;
		}
		bank->Enqueue(transaction_list);

		transaction_list.clear();
	}
	bank->ProcessQueue();	
	bank->Display();
}
