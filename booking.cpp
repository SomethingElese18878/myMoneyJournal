#include "booking.h"

Booking::Booking(){

}

Booking::Booking(float price, QString description)//, QString description, QDateEdit date
{
    this->price = price;
    this->description = description;
    //this->date = date;
}
