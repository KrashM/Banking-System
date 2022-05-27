#include "NormalAccount.hpp"
#include "SavingsAccount.hpp"
#include "PrivilegeAccount.hpp"
#include "Bank.hpp"

int main(){

    Bank myBank("Plamena's bank", "j.k. Studentski grad");

    Customer pesho(1, "Pesho", "j.k. Studentski grad");
    Customer gosho(2, "Gosho", "j.k. Studentski grad");
    Customer mitko(3, "Mitko", "j.k. Studentski grad");

    myBank.addCustomer(pesho);
    myBank.addCustomer(gosho);
    myBank.addCustomer(mitko);

    SavingsAccount peshoAcc(200, time(0), "Pesho", "Hello", "1234", 1, 1.3);
    NormalAccount goshoAcc(800, time(0), "Gosho", "Bye", "5678", 2);
    PrivilegeAccount mitkoAcc(400, time(0), "Mitko", "World", "pl02", 3, 150.5);

    myBank.addAccount(peshoAcc);
    myBank.addAccount(goshoAcc);
    myBank.addAccount(mitkoAcc);

    peshoAcc.display();
    cout << '\n';

    cout << (peshoAcc.withdraw(20) ? "True" : "False") << '\n';
    peshoAcc.deposit(20);
    cout << '\n';
    peshoAcc.display();

    cout << "Listing all customers:\n";
    myBank.listCustomers();
    cout << "Listing all accounts:\n";
    myBank.listAccounts();
    cout << "Listing accounts of gosho:\n";
    myBank.listCustomerAccounts(2);
    cout << "\n\n";

    cout << "Doing transfers\n\n";
    myBank.transfer(50, "1234", "5678");
    myBank.transfer(50, "5678", "1234");

    cout << "Displaying bank info\n";
    myBank.display();

}