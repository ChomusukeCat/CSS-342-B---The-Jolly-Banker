/*	
*	CSS 342 B Program 5: Bank
*	Steven Chau
*	Binary Search Tree class
*	Handles accounts and stores them in nodes
*/
#ifndef BSTREE_H
#define BSTREE_H
#include "account.h"
using namespace std;
class BSTree
{
public:
	BSTree();
	~BSTree();

	bool Insert(Account* acc);
	// retrieve object, first parameter is the ID of the account
	// second parameter holds pointer to found object, NULL if not found
	bool Retrieve(const int& target, Account*& source) const;
	// displays the contents of a tree to cout
	void Display() const;
	void Empty();
	bool isEmpty() const;
private:
	struct Node
	{
		Account* pAcct_;
		Node* right_ = nullptr;
		Node* left_ = nullptr;
	};
	Node* root_ = nullptr;
	Account* RecursiveSearch(Node* root, const int& target) const;
	void RecursiveInsert(Node*& root, Account* target);
	void RecursivePrint(Node* printNode) const;
};
#endif // !BSTREE_H
