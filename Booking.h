#ifndef BOOKING_H
#define BOOKING_H

#include <QString>
//TODO: #include <QDateirgendetwas

class Booking
{
public:
    Booking();
    Booking(float price, std::string description); //, QString description, QDateEdit date
//private:
    float price;
    std::string description;

    //TODO: future
    std::string categorie;
    bool is_periodic;
};


#endif // BOOKING_H
