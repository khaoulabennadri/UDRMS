#ifndef RESTAURANT_H
#define RESTAURANT_H
#include <QString>
#include <QListWidget>

class Restaurant
{
private:
    QString name;
    int mealsServedToday;

public:
    Restaurant();
    Restaurant(QString name);

    QString getName() const;
    int getMealsServedToday() const;
    void serveMeal();
    void resetDay();
    void showMenu(QString mealType, QListWidget* listWidget);
};

#endif