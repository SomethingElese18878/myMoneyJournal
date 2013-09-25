#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <Booking.h>

class Account
{
public:
    Account();
    Account(std::string account_name, float money = 0);

    void setMoney(float money);
    inline float getMoney(){ return money; };

    void setBooking(Booking newBooking);
private:
    float money;
    std::string account_name;

    //TODO:
    static float total_money;
    bool isActive;
};

#endif // ACCOUNT_H
