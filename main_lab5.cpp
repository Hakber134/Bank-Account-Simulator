//
// ECE 220 Lab - Winter 2023 - Programming for Electrical Engineering
// // Lab 1: Play with a Machine
// // Lab 2: Let us Translate
// // Lab 3: Divide and Conquer
// // Lab 4: Modular and Tailored
// ---> Lab 5: Object Oriented
//
//


#include <iostream>
#include <string.h>

using namespace std;


#define MAX_NAME_LEN 40
#define OWN 1
#define RENT 0

// The 1st-level class: BankAccount
class BankAccount {
protected:
    char name[MAX_NAME_LEN];
    int account_number;
    double balance;
public:
    BankAccount();
    BankAccount(char *);
    BankAccount(char *, int, double);

    void printSummary();
    double withdraw(double);
    void deposit(double);
    double getBalance();
    void setName(char *);
    void setAccount_number(int);
    void setBalance(double);
};

// The 2nd-level class: saveBankAccount
class saveBankAccount : public BankAccount { //inheritance of BankAccount
protected:
    double interestRate;
    int MAXnoWithDraws;
    int noWithDraws;

public:
    saveBankAccount(char*name0, int acc_num0, double balance0, double interestRate0, int MAXnoWtdraws0);

    void printSummary();
    double withdraw(double);

    void callInterest();
    void resetWithdraws();
    void transfer(saveBankAccount &acc2, double);

};

// The 3rd-level class: CreditScoreAccount
class CreditScoreAccount : public saveBankAccount {   //inherit from saveBankAccount
protected:
    int age;
    long income;
    bool home_ownership;
    int CreditScore;
public:
    CreditScoreAccount(char*name0, int acc_num0, double balance0, double interestRate0, int MAXnoWtdraws0, int age0, long income0, bool home0);

    void CreditScoreReport();
};


int main(void) {

    // --------------------------------------
    cout << "--Task A2: Display tomAcc--" << endl;
    saveBankAccount tomacc("Tom", 110011, 2000, 0.05, 1);
    tomacc.printSummary();

    cout << "TASK B, Step B2-01" << endl;
    tomacc.deposit(1000);
    tomacc.printSummary();
    cout << "TASK B, Step B2-02" << endl;
    tomacc.withdraw(500);
    tomacc.printSummary();
    cout << "TASK B, Step B2-03" << endl;
    tomacc.withdraw(500);
    tomacc.printSummary();
    cout << "TASK B, Step B2-04" << endl;
    cout << "Current balance: " << tomacc.getBalance() << endl;
    cout << "TASK B, Step B2-05" << endl;
    tomacc.resetWithdraws();
    cout << "Your withdrawal counter was successfully reset to 0." << endl;
    tomacc.printSummary();
    cout << "TASK B, Step B2-06" << endl;
    tomacc.withdraw(500);
    tomacc.printSummary();
    cout << "TASK B, Step B2-07" << endl;
    tomacc.callInterest();
    tomacc.printSummary();

    cout << "TASK B3, create ericAcc" << endl;
    saveBankAccount ericacc("Eric", 220011, 5000, 0.04, 1);
    cout << "TASK B, Step B4-01" << endl;
    ericacc.printSummary();
    cout << "TASK B, Step B4-02" << endl;
    ericacc.transfer(tomacc, 1000);
    cout << "TASK B, Step B4-03" << endl;
    ericacc.printSummary();
    cout << "TASK B, Step B4-04" << endl;
    tomacc.printSummary();

    cout << "Step C2-01" << endl;
    CreditScoreAccount amyCredit("Amy", 330011, 5000, 0.03, 5, 25, 80000, RENT);
    amyCredit.printSummary();
    amyCredit.CreditScoreReport();

    cout << "Step C2-02" << endl;
    CreditScoreAccount kateCredit("Kate", 330022, 5000, 0.03, 5, 35, 120000, OWN);
    kateCredit.printSummary();
    kateCredit.CreditScoreReport();
    // ----------------------------
    return 0;
}

////**********************************************
//// class BankAccount: methods
////**********************************************

BankAccount::BankAccount() {
    name[0] = 0;
    account_number = 0;
    balance = 0.0;
}

BankAccount::BankAccount(char *n) {
    strcpy(name, n);
    account_number = 0;
    balance = 0.0;
}

BankAccount::BankAccount(char *n, int a_no, double bal) {
    strcpy(name, n);
    account_number = a_no;
    balance = bal;
}

void BankAccount::printSummary() {
    cout << "---------------------" << endl;
    cout << "Name: " << name << endl;
    cout << "Account Number: " << account_number << endl;
    cout << "Balance: " << balance << endl;
}

double BankAccount::withdraw(double toWD) {
    if (balance - toWD > 0) {
        balance -= toWD;
        cout << "Withdraw succeed!: " << toWD << endl;
        return toWD; //teng4 modified.
    } else {
        cout << "!!!Sorry, not enough money!!!" << endl;
        cout << "Withdraw failed!: " << toWD << endl;
        return 0;
    }
}

void BankAccount::deposit(double toDep) {
    balance += toDep;
    cout << "Deposit succeed!: " << toDep << endl;
}

double BankAccount::getBalance() {
    return balance;
}


void BankAccount::setName(char *n) {
    strcpy(name, n);
}

void BankAccount::setAccount_number(int a_no) {
    account_number = a_no;
}

void BankAccount::setBalance(double bal) {
    balance = bal;
}

////**********************************************
//// class saveBankAccount: methods
////**********************************************

saveBankAccount::saveBankAccount(char *name, int acc_num, double balance, double interestRate, int MAXnoWtdraws)
    :BankAccount(name, acc_num, balance){
    noWithDraws=0;
    saveBankAccount::interestRate = interestRate;
    saveBankAccount::MAXnoWithDraws = MAXnoWtdraws;
}
void saveBankAccount::printSummary() {
    BankAccount::printSummary();
    cout <<"Interest rate: "<< interestRate << endl;
    cout <<"Number of Withdrawals: "<< noWithDraws << endl;
    cout <<"Max Number of Withdrawals: "<< MAXnoWithDraws << endl;
    cout << "----------------------------" << endl;
}
void saveBankAccount::callInterest() {
    cout << "Interest: " << balance * interestRate << endl;
    balance += balance * interestRate;
    cout <<"New Balance: " << balance << endl;
}

void saveBankAccount::resetWithdraws() {
    noWithDraws = 0;
}

void saveBankAccount::transfer(saveBankAccount &acc2, double amount) {
    if (balance < amount) {
        cout << "Insufficient funds" << endl;
        return;
    }
    cout << "Transfer complete for: " << amount << endl;
    balance -= amount;
    acc2.balance += amount;
}
double saveBankAccount::withdraw(double amount) {
    if (balance < amount) {
        cout << "Insufficient Funds! Current Balance is: " << balance << endl;
        return 0;
    }
    if (noWithDraws >= MAXnoWithDraws) {
        cout << "Task failed. Withdrawal limit reached!" << endl;
        return 0;
    }
    cout << "Withdrawal successful! Withdrawal amount: " << amount << endl;
    balance -= amount;
    noWithDraws++;
    return amount;
}


////**********************************************
//// class CreditScoreAccount: methods
////**********************************************
CreditScoreAccount::CreditScoreAccount(char *name0, int acc_num0, double balance0, double interestRate0,
                                       int MAXnoWtdraws0, int age0, long income0, bool home0)
                                       : saveBankAccount(name0, acc_num0, balance0, interestRate0, MAXnoWtdraws0){
    CreditScoreAccount::age=age0;
    CreditScoreAccount::income=income0;
    CreditScoreAccount::home_ownership=home0;
    CreditScoreAccount::CreditScore=0;
}
void CreditScoreAccount::CreditScoreReport() {
    int age_factor, income_factor, home_factor;
//-----------------------------------
//add your code here (calculating age_factor)
    if (age < 22) {
        age_factor = 100;
    } else if (age >= 22 && age < 26) {
        age_factor = 120;
    } else if (age >= 26 && age < 29) {
        age_factor = 185;
    } else if (age >= 29 && age < 32) {
        age_factor = 200;
    } else if (age >= 32 && age < 37) {
        age_factor = 210;
    } else if (age >= 37 && age < 42) {
        age_factor = 225;
    } else if (age >= 42) {
        age_factor = 250;
    }
//-----------------------------------
//add your code here (calculating income_factor)
    if (income < 10000) {
        income_factor = 120;
    } else if (income >= 10000 && income < 17000) {
        income_factor = 140;
    } else if (income >= 17000 && income < 28000) {
        income_factor = 180;
    } else if (income >= 28000 && income < 35000) {
        income_factor = 200;
    } else if (income >= 35000 && income < 42000) {
        income_factor = 225;
    } else if (income >= 42000 && income < 58000) {
        income_factor = 230;
    } else if (income >= 58000) {
        income_factor = 260;
//-----------------------------------
//calculating home_factor
        if (home_ownership == 1) {
            home_factor = 225;
        } else
            home_factor = 110;
//-----------------------------------
        CreditScore = age_factor + income_factor + home_factor;
        cout << "---------------------" << endl;
        cout << "Credit report for " << name << endl;
        cout << "Age " << age_factor << endl;
        cout << "Income " << income_factor << endl;
        cout << "Home " << home_factor << endl;
        cout << "Credit Score: " << CreditScore << endl;
        cout << "" << endl;
        if (CreditScore < 600)
            cout << "Sorry, " << name << " is not eligible!" << endl;
        else
            cout << "Congratulations!! " << name << " is eligible!" << endl;
        cout << "---------------------" << endl;
    }
}