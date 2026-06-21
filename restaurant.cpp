#include "restaurant.h"
Restaurant::Restaurant() : name("Restaurant"), mealsServedToday(0) {}

Restaurant::Restaurant(QString name) : name(name), mealsServedToday(mealsServedToday) {}

QString Restaurant::getName() const { return name; }

int Restaurant::getMealsServedToday() const { return mealsServedToday; }

void Restaurant::serveMeal() { mealsServedToday++; }

void Restaurant::resetDay()  { mealsServedToday = 0; }

void Restaurant::showMenu(QString mealType, QListWidget* listWidget)
{
    listWidget->clear();

    if (mealType== "Breakfast") {
        listWidget->addItem("Milk");
        listWidget->addItem(" Bread");
        listWidget->addItem(" Eggs");
        listWidget->addItem(" Tea");
    }
    else if (mealType== "Lunch") {
        listWidget->addItem(" Soup");
        listWidget->addItem(" Rice");
        listWidget->addItem(" Chicken");
        listWidget->addItem(" Salad");
    }
    else if (mealType == "Dinner") {
        listWidget->addItem(" Mashed Potato");
        listWidget->addItem(" Juice");
        listWidget->addItem(" Fruit");
        listWidget->addItem(" Cake");
    }
}