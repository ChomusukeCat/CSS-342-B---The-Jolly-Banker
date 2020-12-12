# Bank
Bank simulator, reads in a string of transactions from a file into an in-memory queue. Transactions include: opening accounts, withdrawing/depositing funds, transferring funds, and printing out the transaction history 

You will build a banking application which processes transactions. This banking
application consists of three phases.
1) The program will read in a string of transactions from a file into an in-memory queue.
  These transactions can open accounts, withdraw funds, deposit funds, transfer funds, or ask for
the transactional history to be printed.

2) The program will next read from the queue and process the transactions in order.

3) When the queue has been depleted the program will print out all open accounts and
  balances in those accounts.
Details:
Input:
To test your program a file will be passed in by an argument to the program. The file will
contain a list of transactions that need to be executed. Transactions of the format described
below (see section on transactions) will be contained in this file. There will be one transaction
per line.Assume that the input is well-formed in the file—that is, there are no syntax errors. That
said, there may be errors in the transactions themselves. For instance, a transaction may try to
withdraw more money than there is a fund or try to withdraw for a non-existent fund. See the
section below entitled errors for details.

Client Accounts and Funds:
Each client account contains assets held in up to ten funds. A client account is
represented by a first and last name (two strings) and a unique 4 digit identifier. A fifth digit can
be added to the digit id to represent the individual fund within the account as enumerated
below:

0: Money Market-----------5: Capital Value Fund

1: Prime Money Market----6: Growth Equity Fund


2: Long-Term Bond---------7: Growth Index Fund


3: Short-Term Bond---------8: Value Fund


4: 500 Index Fund-----------9: Value Stock Index

Funds (0, 1) and (2, 3) are joint funds meaning withdraws may take away from related funds if necessary.

For example: Attempting to withdraw from Money Marketwith with insufficient funds may result in funds withdrawn from both Money Market and Prime Money Market if possible.

A client account is opened as a transaction.

Transactions:

There are five types of transactions and each are identified by a character beginning the line.
O: Open a client account with the appropriate funds

D: Deposit assets into a fund

W: Withdraw assets from a fund

T: Transfer assets between funds (can be funds owned by a single client or
transfers between clients)

H: Display the history of all transactions for a client account or for a single fund.

Include errors in the output where appropriate.
After this character key, the account-fund number is given followed by relevant information for
the transaction.
