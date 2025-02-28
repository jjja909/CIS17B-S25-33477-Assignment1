#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <stdexcept>

class BankAccount {
private:
    std::string accountHolderName;
    int accountNumber;
    double balance;
public:
    
    //constructor, exception if initialBalance is negative
    BankAccount(const std::string &name, double initialBalance, int accountNumber);
    
    //Deposit money, exception if negative
    void deposit(double amount);
    
    //withdraw, ex when amt is negative or insufficient.
    void withdraw(double amount);
    
    //return balance
    double getBalance() const;
    
   // get account name
    std::string getAccountHolderName() const;
    
    //get acc number
    int getAccountNumber() const;
    
};


#endif 

