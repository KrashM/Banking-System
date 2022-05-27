#include "Bank.hpp"

Bank::Bank(): name(nullptr), address(nullptr){}
Bank::Bank(const char *name, const char *address): name(new char[strlen(name) + 1]), address(new char[strlen(address) + 1]){

    strcpy(this -> name, name);
    strcpy(this -> address, address);

}
Bank::Bank(const Bank &other){ this -> copy(other); }
Bank::~Bank(){ this -> free(); }
Bank &Bank::operator =(const Bank &other){

    if(this != &other){

        this -> free();
        this -> copy(other);

    }

    return *this;

}

void Bank::free(){

    delete[] this -> name;
    delete[] this -> address;
    for(size_t i = 0; i < this -> customers.size(); i++)
        delete this -> customers[i];
    for(size_t i = 0; i < this -> accounts.size(); i++)
        delete this -> accounts[i];

}
void Bank::copy(const Bank &other){

    this -> name = new char[strlen(other.name) + 1];
    strcpy(this -> name, other.name);
    this -> address = new char[strlen(other.address) + 1];
    strcpy(this -> address, other.address);

    this -> log = other.log;
    this -> customers = other.customers;
    this -> accounts = other.accounts;

}

// TODO: Check if customer id exists
void Bank::addCustomer(const Customer &customer){ this -> customers.pushBack(customer.clone()); }
void Bank::addAccount(const Account &account){ this -> accounts.pushBack(account.clone()); }

bool Bank::deleteCustomer(const u_short customerId){

    for(size_t i = 0; i < this -> customers.size(); i++)
        if(this -> customers[i] -> getId() == customerId){

            delete this -> customers[i];
            this -> customers.removeAt(i);
            return true;

        }

    return false;

}
bool Bank::deleteAccount(const u_short customerId, const char *iban){

    for(size_t i = 0; i < this -> accounts.size(); i++)
        if(this -> accounts[i] -> getUserId() == customerId && !strcmp(this -> accounts[i] -> getIBAN(), iban)){

            delete this -> accounts[i];
            this -> accounts.removeAt(i);
            return true;

        }

        return false;

}

void Bank::listCustomers() const{ for(size_t i = 0; i < this -> customers.size(); i++) this -> customers[i] -> display(); }
void Bank::listAccounts() const{ for(size_t i = 0; i < this -> accounts.size(); i++) this -> accounts[i] -> display(); }
void Bank::listCustomerAccounts(const u_short userId) const{

    for(size_t i = 0; i < this -> accounts.size(); i++)
        if(this -> accounts[i] -> getUserId() == userId)
            this -> accounts[i] -> display();

}

void Bank::exportLog() const{ cout << "Logging\n"; }

void Bank::transfer(const double amount, const char *fromIBAN, const char *toIBAN){

    Account *toAcc = nullptr;

    for(size_t i = 0; i < this -> accounts.size(); i++){

        if(!strcmp(this -> accounts[i] -> getIBAN(), toIBAN)) toAcc = this -> accounts[i];
        if(!strcmp(this -> accounts[i] -> getIBAN(), fromIBAN)){

            if(this -> accounts[i] -> withdraw(amount)){

                if(toAcc == nullptr)
                    for(size_t j = i + 1; j < this -> accounts.size(); j++)
                        if(!strcmp(this -> accounts[i] -> getIBAN(), toIBAN))
                            toAcc = this -> accounts[i];
                toAcc -> deposit(amount);

            }

            return;

        }

    }

}

void Bank::display() const{

    cout << "Bank name is: " << this -> name
        << "\nAddress is: " << this -> address << "\n\n";

    for(size_t i = 0; i < this -> customers.size(); i++)
        this -> customers[i] -> display();

    for(size_t i = 0; i < this -> accounts.size(); i++)
        this -> accounts[i] -> display();

}