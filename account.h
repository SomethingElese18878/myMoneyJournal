#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
    Account();
    void setMoney();
    inline float getMoney(){ return money; };
private:
    float money;
};

#endif // ACCOUNT_H
