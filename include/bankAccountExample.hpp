
class BankAccount {

  private:

    double balance;

  public:

    BankAccount(double amount);

    BankAccount();

    void deposite(double amount);

    void withdraw(double amount);

    double getBalance();

};
