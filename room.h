#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <QVector>
#include <QTextStream>
#include <stdexcept>

class Room
{
private:
    int number;
    int capacity;
    int occupied;
    QVector<QString> students;

public:
    Room();
    Room(int roomNumber, int roomCapacity);

    int getNumber() const;
    int getCapacity() const;
    int getOccupied() const;
    int getFreeSpots() const;
    QString getStatus() const;
    QString getStudentsList() const;

    void setNumber(int n);
    void setCapacity(int c);

    bool isFull() const;
    bool addStudent(QString studentId);
    bool removeStudent(QString studentId);

    bool operator==(const Room& other) const;

    friend QTextStream& operator<<(QTextStream& stream, const Room& room);
};

#endif // ROOM_H