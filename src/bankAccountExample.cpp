#include "main.h"

BankAccount::BankAccount() {
  balance = 0;
}

BankAccount::BankAccount(double amount) {
  balance = amount;

}

void BankAccount::deposite(double amount) {
  //balance = balance + amount; below is same method
  balance+= amount;
}

void BankAccount::withdraw(double amount) {
  balance-= amount;
}

double BankAccount::getBalance() {
  return balance;
}
