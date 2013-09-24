#include "account.h"

Account::Account(std::string account_name, float money)
{
    this->money = money;
    this->account_name = account_name;
}

void Account::setMoney(float money){
    this->money += money;
    std::cout << "money was set to: " << this->money << std::endl;
}
