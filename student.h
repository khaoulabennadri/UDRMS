#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student {
private:
    int id;
    QString name;
    int roomNumber;

public:
    Student(int id, const QString &name, int roomNumber);
    int getId() const;
    QString getName() const;
    int getRoomNumber() const;
    void setRoomNumber(int roomNumber);
};

#endif // STUDENT_H