#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <ctime>
#include <limits>
#include "BankAccount.h"

BankAccount::BankAccount(const std::string &name, double initialBalance, int accNumber)
        : accountHolderName(name), balance(initialBalance), accountNumber(accNumber)
{
    if (initialBalance < 0) {
        throw std::invalid_argument("Initial balance can't be negative.");
    }
}

void BankAccount::deposit(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Deposit amount cannot be negative.");
    }
    balance += amount;
}

void BankAccount::withdraw(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Withdrawal amount cannot be negative.");
    }
    if (amount > balance) {
        throw std::runtime_error("Insufficient funds");
    }
    balance -= amount;
}

double BankAccount::getBalance() const {
    return balance;
}

std::string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}

int BankAccount::getAccountNumber() const {
    return accountNumber;
}

//5 digit account # (between 10000 and 99999)
int generateUniqueAccountNumber(std::unordered_set<int>& usedAccountNumbers) {
    int num;
    do {
        num = rand() % 90000 + 10000; //random number
    } while (usedAccountNumbers.find(num) != usedAccountNumbers.end());
    usedAccountNumbers.insert(num);
    return num;
}

//exception clear input
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
 * 
 */

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    //Containers for accounts
    std::unordered_map<std::string, BankAccount> accounts;
    std::unordered_set<int> usedAccountNumbers;
    
    int mainChoice;
    while (true) {
            std::cout << "System Bank System\n";               
            std::cout << "1. Create Account\n";
            std::cout << "2. Sign in to Existing Account\n";
            std::cout << "3. Exit\n";        
        std::cout << "Enter your Choice: ";
        std::cin >> mainChoice;
        
        if (std::cin.fail()) {
            clearInput();
            std::cout << "Invalid input. Enter a valid number.\n";
            continue;
        }
        
            switch (mainChoice) {
                //Create Account
                case 1: {
                    std::string name;
                    double initialBalance;
                    
                    std::cout << "Enter account name: ";
                    std::cin >> name;
                    
                    // check for unique account name
                    if (accounts.find(name) != accounts.end()) {
                        std::cout << "An account with this name already exists\n";
                        break;
                    }
                    
                    std::cout <<"Enter initial balance: ";
                    std::cin >> initialBalance;
                    if (std::cin.fail()) {
                        clearInput();
                        std::cout << "Invalid input, try again\n";
                        break;
                    }
                    
                    try {
                        int accNumber = generateUniqueAccountNumber(usedAccountNumbers);
                        BankAccount newAccount(name, initialBalance, accNumber);
                        accounts.emplace(name, newAccount);
                        std::cout << "Account creation successful! Your account number is: " << accNumber << "\n";
                    } catch (const std::exception &e) {
                        std::cout << "Error creating account: " << e.what() << "\n";                        
                    }
                    break;
                }
                //Sign in
                case 2: {
                    std::string name;
                    std::cout << "Enter account name to sign in: ";
                    std::cin >> name;
                    
                    auto it = accounts.find(name);
                    if (it == accounts.end()) {
                        std::cout << "Account not found. Try again.\n";
                        break;
                    }
                    
                    //menu
                    BankAccount &currentAccount = it->second;
                    int accountChoice;
                    while (true) {
                        std::cout << "\n Account menu for " << currentAccount.getAccountHolderName()
                                << "(Account Number: " << currentAccount.getAccountNumber() << ")\n";
                        std::cout << "1. Deposit Money\n";
                        std::cout << "2. Withdraw Money\n";
                        std::cout << "3. Check Balance\n";
                        std::cout << "4. Sign Out\n";
                        std::cin >> accountChoice;
                        
                        if (std::cin.fail()) {
                            clearInput();
                            std::cout << "Invalid input. Enter a valid number.\n";
                            continue;
                        }
                        
                        //deposit
                        if (accountChoice == 1) { 
                            double amount;
                            std::cout << "Enter amount to deposit: ";
                            std::cin >> amount;
                            if (std::cin.fail()) {
                                clearInput();
                                std::cout << "Invalid input. Enter a valid number.";
                                        continue;
                            }
                            try {
                                currentAccount.deposit(amount);
                                std::cout << "Deposit successful. New Balance is " << currentAccount.getBalance() << "\n";
                                
                            } catch (const std::exception &e) {
                                std::cout << "Error: " << e.what() << "\n";
                            }
                            //check balance
                        } else if (accountChoice == 3) {
                            std::cout << "Current balance: " << currentAccount.getBalance() << "\n";
                            //sign out
                        } else if (accountChoice == 4) {
                            std::cout << "Signing out...\n";
                            break;
                            
                        } else {
                            std::cout << "Invalid Choice. Please try again.\n";
                        }
                    }
                    break;
                }
                //Exit
                case 3: {
                    std::cout << "Exiting the system.\n";
                    return 0;
                }
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } 
           
    return 0;
}

