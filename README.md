# Bank
Bank simulator, reads in a string of transactions from a file into an in-memory queue. Transactions include: opening accounts, withdrawing/depositing funds, transferring funds, and printing out the transaction history 

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

For example: Attempting to withdraw from Money Market with insufficient funds may result in funds being withdrawn from both Money Market and Prime Money Market if possible.

A client account is opened as a transaction.

Transactions:

There are five types of transactions and each are identified by a character beginning the line.
O: Open a client account with the appropriate funds

D: Deposit assets into a fund

W: Withdraw assets from a fund

T: Transfer assets between funds (can be funds owned by a single client or
transfers between clients)

H: Display the history of all transactions for a client account or for a single fund.

