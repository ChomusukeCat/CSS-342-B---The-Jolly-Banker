#include "bstree.h"

BSTree::BSTree()
{
	root_ = new Node();
	root_->pAcct_ = new Account("dummy", "account", -1000);
}
BSTree::~BSTree() 
{
	Empty();
}

bool BSTree::Insert(Account* account)
{
	RecursiveInsert(root_, account);
	return true;
}

bool BSTree::Retrieve(const int& target, Account*& source) const
{
	Account* temp = RecursiveSearch(root_, target);

	if (temp == nullptr)
	{
		return false;
	}
	else
	{
		source = temp;
		return true;
	}
}

void BSTree::Display() const
{
	if (root_ == nullptr || root_->pAcct_->get_id() == -1000)
	{
		cerr << "ERROR: Account list is empty" << endl;
	}
	else
	{
		RecursivePrint(root_);
	}

}
void BSTree::Empty()
{
	delete root_;
	root_ = nullptr;
}

bool BSTree::isEmpty() const
{
	if (root_ == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Private (helper) functions
Account* BSTree::RecursiveSearch(Node* node, const int& target) const
{
	if (node == nullptr)
	{
		return nullptr;
	}
	else if (target == (node->pAcct_->get_id()))
	{
		return (node->pAcct_);
	}
	else if (target < (node->pAcct_->get_id()))
	{
		return RecursiveSearch(node->left_, target);
	}
	else
	{
		return RecursiveSearch(node->right_, target);
	}
}

void BSTree::RecursiveInsert(Node*& node, Account* target)
{
	if (node == nullptr || node->pAcct_->get_id() == -1000)
	{
		node = new Node();
		node->pAcct_ = target;
		return;
	}
	else if (*target < *node->pAcct_)
	{
		RecursiveInsert(node->left_, target);
	}
	else
	{
		RecursiveInsert(node->right_, target);
	}
}

void BSTree::RecursivePrint(Node* current) const
{
	if (current->right_ != nullptr && current->left_ != nullptr)
	{
		RecursivePrint(current->right_);
		cout << *(current->pAcct_) << endl;
		RecursivePrint(current->left_);
	}
	else if (current->left_ != nullptr)
	{
		cout << *(current->pAcct_) << endl;
		RecursivePrint(current->left_);
	}
	else if (current->right_ != nullptr)
	{
		cout << *(current->pAcct_) << endl;
		RecursivePrint(current->right_);
	}
	else
	{
		cout << *(current->pAcct_) << endl;
	}

}