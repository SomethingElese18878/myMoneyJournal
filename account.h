#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

class Account
{
public:
    Account();
    void setMoney(float money);
    inline float getMoney(){ return money; };
private:
    float money;
};

#endif // ACCOUNT_H
