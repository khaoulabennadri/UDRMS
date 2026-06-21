#include "student.h"

Student::Student() : age(0), room(0) {}

Student::Student(QString id, QString name, int age, int room, QString academicYear)
    : id(id), name(name), age(age), room(room), academicYear(academicYear) {}

QString Student::getId() const
{
    return id;
}

QString Student::getName() const { return name; }
int Student::getAge() const { return age; }
int Student::getRoom() const { return room; }
QString Student::getAcademicYear() const { return academicYear; }

void Student::setId(QString id) { this->id = id; }
void Student::setName(QString name) { this->name = name; }
void Student::setAge(int age) { this->age = age; }
void Student::setRoom(int room) { this->room = room; }
void Student::setAcademicYear(QString year) { academicYear = year; }