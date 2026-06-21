#ifndef STUDENT_H
#define STUDENT_H
#include <QString>

class Student {
private:
    QString id;
    QString name;
    int age;
    int room;
    QString academicYear;

public:
    Student();
    Student(QString id, QString name, int age, int room, QString academicYear);

    QString getId() const;
    QString getName() const;
    int getAge() const;
    int getRoom() const;
    QString getAcademicYear() const;

    void setId(QString id);
    void setName(QString name);
    void setAge(int age);
    void setRoom(int room);
    void setAcademicYear(QString year);
};
#endif