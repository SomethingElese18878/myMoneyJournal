#include "Booking.h"

Booking::Booking(){

}

Booking::Booking(float price, std::string description)//, QString description, QDateEdit date
{
    this->price = price;
    this->description = description;
    //this->date = date;
}
