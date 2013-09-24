#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

class Account
{
public:
    Account();
    Account(std::string account_name, float money);
    void setMoney(float money);
    inline float getMoney(){ return money; };
private:
    float money;
    std::string account_name;
};

#endif // ACCOUNT_H
