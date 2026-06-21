#include "dormitory.h"
Dormitory::Dormitory()
    : name(""), capacity(0) {}

Dormitory::Dormitory(QString name, int capacity)
    : name(name), capacity(capacity) {}

QString Dormitory::getName()const
{
    return name;
}

int Dormitory::getCapacity()const
{
    return capacity;
}

void Dormitory::setName(QString n)
{
    name =n;
}

void Dormitory::setCapacity(int c)
{
    capacity = c;
}

Restaurant& Dormitory::getRestaurant()
{
    return restaurant;
}