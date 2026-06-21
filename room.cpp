#include "room.h"

Room::Room()
{
    number = 0;
    capacity = 0;
    occupied = 0;
}

Room::Room(int roomNumber, int roomCapacity)
{
    number = roomNumber;
    capacity = roomCapacity;
    occupied = 0;
}

int Room::getNumber() const
{
    return number;
}

int Room::getCapacity() const
{
    return capacity;
}

int Room::getOccupied() const
{
    return occupied;
}

int Room::getFreeSpots() const
{
    return capacity - occupied;
}

QString Room::getStatus() const
{
    if (isFull())
        return "Full";
    else
        return "Available";
}

QString Room::getStudentsList() const
{
    return students.join(", ");
}

// ===== Setters =====
void Room::setNumber(int n)
{
    number = n;
}

void Room::setCapacity(int c)
{
    capacity = c;
    // If new capacity is smaller than occupied, fix occupied
    if (occupied > capacity)
        occupied = capacity;
}

bool Room::isFull() const
{
    if (occupied >= capacity)
        return true;
    else
        return false;
}

bool Room::addStudent(QString studentId)
{
    if (isFull())
        throw std::runtime_error("Room is full!");
    students.append(studentId);
    occupied = occupied + 1;
    return true;
}

bool Room::removeStudent(QString studentId)
{
    if (!students.contains(studentId))
        return false;
    students.removeOne(studentId);
    occupied = occupied - 1;
    return true;
}

bool Room::operator==(const Room& other) const
{
    return number == other.number;
}

QTextStream& operator<<(QTextStream& out, const Room& room)
{
    out << "Room " << room.getNumber() << ": "
           << room.getOccupied() << "/" << room.getCapacity()
           << " (" << room.getStatus() << ")";
    return out;
}