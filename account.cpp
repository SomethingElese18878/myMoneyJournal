#include "account.h"

Account::Account(){

}

Account::Account(std::string account_name, float money)
{
    std::cout << "Account " << account_name << " will created with: " << money << " bugs" << std::endl;
    this->money = money;
    this->account_name = account_name;


}

void Account::setMoney(float money){
    this->money += money;
    std::cout << "Account: " << this->account_name << std::endl;
    std::cout << "money was set to: " << this->money << std::endl;
}
