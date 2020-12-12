#include "bank.h"

Bank::Bank()
{
}

Bank::~Bank()
{
}

//opens new account
bool Bank::Open(string first_name, string last_name, int id)
{
	if (id < 1000 || id > 9999)
	{
		cerr << "ERROR: ID must be 4 digits" << endl;
		return false;
	}
	Account* new_acc = new Account(first_name, last_name, id);
	//if acc with given id already exists
	if (accounts_tree_.Retrieve(id, new_acc))
	{
		cerr << "ERROR: Open account failed. Account with id: " << id << " already exists" << endl;
		return false;
	}
	else
	{
		accounts_tree_.Insert(new_acc);
		return true;
	}
}

//deposits funds into appropriate fund option
bool Bank::Deposit(int id, int fund_id, int amount)
{
	Account* temp;
	if (accounts_tree_.Retrieve(id, temp))
	{
		temp->Deposit(fund_id, amount);
		return true;
	}
	else
	{
		cerr << "ERROR: Deposit failed. Account with id: " << id << " does not exist" << endl;
		return false;
	}
	
}

//removes funds from appropriate fund option
bool Bank::Withdraw(int id, int fund_id, int amount)
{
	Account* temp;
	if (accounts_tree_.Retrieve(id, temp))
	{
		temp->Withdraw(fund_id, amount);
		return true;
	}
	else
	{
		cerr << "ERROR: Withdraw failed. Account with id: " << id << " does not exist" << endl;
		return false;
	}
}

//prints history of given account
bool Bank::History(int id, int fund_id)
{
	Account* temp;

	if (accounts_tree_.Retrieve(id, temp))
	{
		temp->ShowHistory(fund_id);
		return true;
	}
	else
	{
		cerr << "ERROR: Show history failed. Account with id: " << id << " does not exist" << endl;
		return false;
	} 
}


bool Bank::Transfer(int src_id, int src_fund_id, int amount, int dest_id, int dest_fund_id)
{
	Account* src;
	Account* dest;
	
	//check if given accounts are valid
	if (!accounts_tree_.Retrieve(src_id, src))
	{
		cerr << "ERROR: Transfer failed. Account with id: " << src_id << " does not exist" << endl;
		return false;
	}
	if (!accounts_tree_.Retrieve(dest_id, dest))
	{
		cerr << "ERROR: Transfer failed. Account with id: " << dest_id << " does not exist" << endl;
		return false;
	}
	//check if source account has enough funds to transfer to destination acc.
	if (src->TWithdraw(src_id, src_fund_id, amount, dest_id, dest_fund_id))
	{
		dest->TDeposit(src_id, src_fund_id, amount, dest_id, dest_fund_id);
		return true;
	}
	else
	{
		cerr << "ERROR: Transfer failed. Account with id: " << src_id << " does not have sufficient funds" << endl;
		return false;
	}
}

bool Bank::Enqueue(vector<string> transaction)
{
	transaction_queue_.push(transaction);
	return true;
}

bool Bank::ProcessQueue()
{
	vector<string> transaction;
	while (!transaction_queue_.empty())
	{
		transaction = transaction_queue_.front();

		if (transaction[0] == "O")
		{
			Open(transaction[2], transaction[1], stoi(transaction[3]));
		}
		else if (transaction[0] == "D")
		{
			Deposit(stoi(transaction[1]), stoi(transaction[2]), stoi(transaction[3]));
		}
		else if (transaction[0] == "W")
		{
			Withdraw(stoi(transaction[1]), stoi(transaction[2]), stoi(transaction[3]));
		}
		else if (transaction[0] == "T")
		{
			Transfer(stoi(transaction[1]), stoi(transaction[2]), stoi(transaction[3]), stoi(transaction[4]), stoi(transaction[5]));
		}
		else if (transaction[0] == "H")
		{
			if (transaction[1].size() == 5)
			{
				int fund_id = stoi(transaction[1]) % 10;
				int acc_id = stoi(transaction[1]) / 10;
				History((acc_id), (fund_id));
			}
			else
			{
				History(stoi(transaction[1]), -1);
			}
		}
		transaction_queue_.pop();
	}

	cout << endl;
	cout << "Processing Done. Printing final balances..." << endl;
	cout << endl;
	return true;
}

void Bank::Display() const
{
	accounts_tree_.Display();
}


