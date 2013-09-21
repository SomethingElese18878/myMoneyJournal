#ifndef BOOKING_H
#define BOOKING_H

#include <QString>
//TODO: #include <QDateirgendetwas

class Booking
{
public:
    Booking();
    Booking(float price, QString description); //, QString description, QDateEdit date
//private:
    float price;
    QString description;
    QString categorie; //TODO: future
};


#endif // BOOKING_H
