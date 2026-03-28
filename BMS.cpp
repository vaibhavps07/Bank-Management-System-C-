#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

// Color functions
void Green(){ cout<<"\033[32m"; }
void Yellow(){ cout<<"\033[33m"; }
void Blue(){ cout<<"\033[34m"; }
void Magenta(){ cout<<"\033[35m"; }
void Reset(){ cout<<"\033[0m"; }

class bankAccount {
private:
    string bankName = "TCBOI";
    int bankCode;
    string accountHolderName;
    string accountNumber;
    string accountPassword;
    string addharNumber;
    string email;
    string phoneNumber;
    double balance;
    vector<string> transactionHistory;

public:
    void savetoFile();
    void loadFromFile();
    void mainMenu();
    void createAccount();
    void loginBankAccount();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();
    void accountDetails();
    void allTransactionHistory();
};

// Save data
void bankAccount::savetoFile() {
    ofstream file("data/" + accountNumber + ".txt");

    if (file.is_open()) {
        file << accountHolderName << endl;
        file << accountNumber << endl;
        file << accountPassword << endl;
        file << addharNumber << endl;
        file << email << endl;
        file << phoneNumber << endl;
        file << balance << endl;

        for (auto t : transactionHistory) {
            file << t << endl;
        }
        file.close();
    }
}

// Load data
void bankAccount::loadFromFile() {
    ifstream file("data/" + accountNumber + ".txt");

    if (file.is_open()) {
        getline(file, accountHolderName);
        getline(file, accountNumber);
        getline(file, accountPassword);
        getline(file, addharNumber);
        getline(file, email);
        getline(file, phoneNumber);
        file >> balance;
        file.ignore();

        string t;
        while (getline(file, t)) {
            transactionHistory.push_back(t);
        }
        file.close();
    }
}

// Main menu
void bankAccount::mainMenu() {
    int choice;

    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Details\n5. History\n6. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");

        switch (choice) {
            case 1: depositMoney(); break;
            case 2: withdrawMoney(); break;
            case 3: checkBalance(); break;
            case 4: accountDetails(); break;
            case 5: allTransactionHistory(); break;
            case 6: cout << "Logged out\n"; break;
            default: cout << "Invalid\n";
        }
    } while (choice != 6);
}

// Create account
void bankAccount::createAccount() {
    Green();
    cout << "Create Account\n";
    Reset();

    cout << "Name: ";
    getline(cin, accountHolderName);

    cout << "Email: ";
    getline(cin, email);

    cout << "Phone: ";
    getline(cin, phoneNumber);

    cout << "Aadhar: ";
    getline(cin, addharNumber);

    cout << "Password: ";
    getline(cin, accountPassword);

    balance = 500;

    ifstream file("Tasin-Coder-Bank-Of-India.txt");
    file >> bankCode;
    file.close();

    ofstream out("Tasin-Coder-Bank-Of-India.txt");
    out << bankCode + 1;
    out.close();

    accountNumber = bankName + to_string(bankCode);

    transactionHistory.push_back("Deposit :- 500");

    cout << "Account Created!\n";
    cout << "Account No: " << accountNumber << endl;

    savetoFile();
}

// Login
void bankAccount::loginBankAccount() {
    string acc, pass;

    cout << "Account No: ";
    getline(cin, acc);

    accountNumber = acc;

    ifstream file("data/" + acc + ".txt");

    if (!file.is_open()) {
        cout << "Account not found\n";
        return;
    }

    loadFromFile();

    cout << "Password: ";
    getline(cin, pass);

    if (pass == accountPassword) {
        cout << "Login success\n";
        mainMenu();
    } else {
        cout << "Wrong password\n";
    }
}

// Deposit
void bankAccount::depositMoney() {
    double amt;
    cout << "Enter amount: ";
    cin >> amt;
    cin.ignore();

    if (amt > 0) {
        balance += amt;
        transactionHistory.push_back("Deposit :- " + to_string(amt));
        savetoFile();

        cout << "New Balance: " << balance << endl;
    }
}

// Withdraw
void bankAccount::withdrawMoney() {
    double amt;
    cout << "Enter amount: ";
    cin >> amt;
    cin.ignore();

    if (amt > 0 && amt <= balance) {
        balance -= amt;
        transactionHistory.push_back("Withdraw :- " + to_string(amt));
        savetoFile();

        cout << "New Balance: " << balance << endl;
    } else {
        cout << "Invalid\n";
    }
}

// Balance
void bankAccount::checkBalance() {
    cout << "Balance: " << balance << endl;
}

// Details
void bankAccount::accountDetails() {
    Magenta();
    cout << "Account Details\n";
    Reset();

    cout << "Name: " << accountHolderName << endl;
    cout << "Account No: " << accountNumber << endl;
    cout << "Balance: " << balance << endl;
}

// History
void bankAccount::allTransactionHistory() {
    cout << "History:\n";
    for (auto t : transactionHistory) {
        cout << t << endl;
    }
}

// Main
int main() {
    bankAccount acc;
    int choice;

    do {
        cout << "\n1. Create Account\n2. Login\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");

        switch (choice) {
            case 1: acc.createAccount(); break;
            case 2: acc.loginBankAccount(); break;
            case 3: cout << "Bye\n"; break;
            default: cout << "Invalid\n";
        }
    } while (choice != 3);

    return 0;
}