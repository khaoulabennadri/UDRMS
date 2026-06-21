#ifndef DORMITORY_H
#define DORMITORY_H

#include <QString>
#include <QVector>
#include "room.h"//each dorm has rooms-> composition
#include "restaurant.h"//composition

class Dormitory
{
private:
    QString name;
    int capacity;
    Restaurant restaurant;   //composition

public:

    Dormitory();
    Dormitory(QString name,int capacity);

    // Getters
    QString getName() const;
    int getCapacity() const;

    // Setters
    void setName(QString name);
    void setCapacity(int capacity);

    Restaurant& getRestaurant();
};

#endif // DORMITORY_H