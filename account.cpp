#include "account.h"
Account::Account(string first, string last, int id)
{
	first_name_ = first;
	last_name_ = last;
	acc_id_ = id;

	funds_[0] = new Funds("Money Market");
	funds_[1] = new Funds("Prime Money Market");
	funds_[2] = new Funds("Long-Term Bond");
	funds_[3] = new Funds("Short-Term Bond");
	funds_[4] = new Funds("500 Index Fund");
	funds_[5] = new Funds("Capital Value Fund");
	funds_[6] = new Funds("Growth Equity Fund");
	funds_[7] = new Funds("Growth Index Fund");
	funds_[8] = new Funds("Value Fund");
	funds_[9] = new Funds("Value Stock Index");

	history_[0] = new Transaction("Money Market");
	history_[1] = new Transaction("Prime Money Market");
	history_[2] = new Transaction("Long-Term Bond");
	history_[3] = new Transaction("Short-Term Bond");
	history_[4] = new Transaction("500 Index Fund");
	history_[5] = new Transaction("Capital Value Fund");
	history_[6] = new Transaction("Growth Equity Fund");
	history_[7] = new Transaction("Growth Index Fund");
	history_[8] = new Transaction("Value Fund");
	history_[9] = new Transaction("Value Stock Index");
}

Account::~Account()
{
}

bool Account::Deposit(int fund_id, int amount)
{
	string transaction = "D " + to_string(acc_id_) + to_string(fund_id) + " " + to_string(amount);
	if (amount < 0)
	{
		cerr << "ERROR: Cannot deposit negative funds" << endl;
		history_[fund_id]->Record(transaction + "(FAILED)");
		return false;
	}
	else
	{
		funds_[fund_id]->Deposit(amount);
		history_[fund_id]->Record(transaction);
		return true;
	}
}

bool Account::Withdraw(int fund_id, int amount)
{
	string transaction = "W " + to_string(acc_id_) + to_string(fund_id) + " " + to_string(amount);
	if (amount < 0)
	{
		cerr << "ERROR: Cannot withdraw negative funds" << endl;
		history_[fund_id]->Record(transaction + "(FAILED)");
		return false;
	}
	else if (funds_[fund_id]->get_balance() >= amount)
	{
		funds_[fund_id]->Withdraw(amount);
		history_[fund_id]->Record(transaction);
	}
	//check funds in (if applicable) joint fund
	else if (JointFundWithdraw(fund_id, amount))
	{
		return true;
	}
	//if amount exceeds current balance
	else
	{
		cerr << "ERROR: Not enough funds to withdraw $" << amount << " from " << get_name() << " " << funds_[fund_id]->get_fund_name() << endl;
		history_[fund_id]->Record(transaction + "(Failed)");
		return false;
	}
	return true;
}
//helper function for transfer
bool Account::TDeposit(int src_acc_id, int src_fund_id, int amount, int dest_acc_id, int dest_fund_id)
{
	string transaction = "T " + to_string(src_acc_id) + to_string(src_fund_id) + " " + to_string(amount) + " " + to_string(dest_acc_id) + to_string(dest_fund_id);
	if (amount < 0)
	{
		cerr << "ERROR: Cannot deposit negative funds" << endl;
		history_[dest_fund_id]->Record(transaction + "(FAILED)");
		return false;
	}
	else
	{
		funds_[dest_fund_id]->Deposit(amount);
		history_[dest_fund_id]->Record(transaction);
		return true;
	}
}
//helper function for transfer
bool Account::TWithdraw(int src_acc_id, int src_fund_id, int amount, int dest_acc_id, int dest_fund_id)
{
	string transaction = "T " + to_string(src_acc_id) + to_string(src_fund_id) + " " + to_string(amount) + " " + to_string(dest_acc_id) + to_string(dest_fund_id);
	if (amount < 0)
	{
		cerr << "ERROR: Cannot withdraw negative funds" << endl;
		history_[src_fund_id]->Record(transaction + "(FAILED)");
		return false;
	}
	else if (funds_[src_fund_id]->get_balance() >= amount)
	{
		funds_[src_fund_id]->Withdraw(amount);
		history_[src_fund_id]->Record(transaction);
	}
	//check funds in (if applicable) joint fund
	else if (JointFundWithdraw(src_fund_id, amount))
	{
		return true;
	}
	//if amount exceeds current balance
	else
	{
		cerr << "ERROR: Not enough funds to withdraw $" << amount << " from " << get_name() << " " << funds_[src_fund_id]->get_fund_name() << endl;
		history_[src_fund_id]->Record(transaction + "(Failed)");
		return false;
	}
	return true;
}

void Account::ShowHistory(int fund_id) const
{
	vector<string> temp;
	//case for printing out full history
	if(fund_id == -1)
	{
		cout << "Transaction History for " << this->get_name() << endl;
		for (int id = 0; id < 10; id++)
		{
			temp = history_[id]->get_history();
			//if no records/history, skip this fund
			if (history_[id]->get_history().empty())
			{
			}
			else
			{
				cout << funds_[id]->get_fund_name() << ": $";
				cout << funds_[id]->get_balance() << endl;
				//print each record
				for (auto it = temp.begin(); it < temp.end(); it++)
				{
					cout << "  " + *it << endl;
				}
			}
			
		}
				
	}
	//only print requested fund
	else
	{
		cout << "Transaction History for " << this->get_name() << endl;
		temp = history_[fund_id]->get_history();
		cout << funds_[fund_id]->get_fund_name() << ": $";
		cout << funds_[fund_id]->get_balance() << endl;
		for (auto it = temp.begin(); it < temp.end(); it++)
		{
			cout << "  " + *it << endl;
		}
	}
}

int Account::get_id() const
{
	return acc_id_;
}

string Account::get_name() const
{
	return first_name_ + " " + last_name_;
}

int Account::get_funds(int fund_id) const
{
	for (int id = 0; id < sizeof(funds_); id++)
	{
		if (fund_id == id)
		{
			return funds_[id]->get_balance();
		}
		else
		{
			return 0;
		}
	}
	return true;
}

bool Account::operator==(const Account& other) const
{
	if (this->get_id() == other.get_id())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Account::operator<(const Account& other) const
{
	if (this->get_id() < other.get_id())
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& out_stream, const Account& acc)
{
	out_stream << acc.get_name() << ", ID: " << acc.get_id() << endl;
	for (int id = 0; id < 10; id++)
	{
		out_stream << acc.funds_[id]->get_fund_name() << ": $";
		out_stream << acc.funds_[id]->get_balance() << endl;
	}
	return out_stream;
}
//Private function
//handles joint fund withdraw cases
bool Account::JointFundWithdraw(int fund_id, int amount)
{
	int joint_fund_id = -1;
	//determine joint fund given main fund id
	switch(fund_id)
	{
	case 0:
		joint_fund_id = 1;
		break;
	case 1:
		joint_fund_id = 0;
		break;
	case 2:
		joint_fund_id = 3;
		break;
	case 3:
		joint_fund_id = 2;
		break;
	default:
		return false;
	}

	int remaining = funds_[fund_id]->get_balance() - amount;
	//check if joint fund has enough in balance
	if (funds_[joint_fund_id]->get_balance() >= abs(remaining))
	{
		//withdraw from main fund
		int new_amount = amount - abs(remaining);
		string transaction = "W " + to_string(acc_id_) + to_string(fund_id) + " " + to_string(new_amount);
		funds_[fund_id]->Withdraw(abs(new_amount));
		history_[fund_id]->Record(transaction);

		//withdraw from joint fund
		funds_[joint_fund_id]->Withdraw(abs(remaining));
		transaction = "W " + to_string(acc_id_) + to_string(joint_fund_id) + " " + to_string(abs(remaining));
		history_[joint_fund_id]->Record(transaction);
		return true;
	}
	else
	{
		cerr << "ERROR: Joint Fund " << funds_[joint_fund_id]->get_fund_name() << " has insufficient funds to complete withdraw" << endl;
		return false;
	}
}


