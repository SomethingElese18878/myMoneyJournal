#include "account.h"

Account::Account()
{
    this->money = 0;
}

void Account::setMoney(float money){
    this->money += money;
    std::cout << "money was set to: " << this->money << std::endl;
}
