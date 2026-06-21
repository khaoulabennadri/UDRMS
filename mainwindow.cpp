#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QColor>
#include <QFile>
#include <QTextStream>
#include "room.h"
#include "student.h"
#include "dormitory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tab_6->setStyleSheet(
        "QWidget#tab_6 {"
        "border-image: url(C:/Users/admin/Downloads/photo_2026-06-19_21-48-10.jpg) 0 0 0 0 stretch stretch;"
        "}"
        );
    ui->tab_4->setStyleSheet(
        "QWidget#tab_4 {"
        "border-image: url(C:/Users/admin/Downloads/photo_2026-06-19_12-20-41.jpg) stretch;"
        "}"
        );
    ui->tab_3->setContentsMargins(0, 0, 0, 0);
    ui->tab_3->setStyleSheet(
        "#tab_3 {"
        "margin: 0px;"
        "padding: 0px;"
        "border: none;"
        "border-image: url(C:/Users/admin/Downloads/photo_2026-06-19_13-27-46.jpg) 0 0 0 0 stretch stretch;"
        "}"
        );
    ui->Students->setStyleSheet(
        "QWidget#Students {"
        "border-image: url(C:/Users/admin/Downloads/Telegram Desktop/photo_2026-06-18_19-10-24.jpg);"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "background-attachment: fixed;"
        "}"
        "QPushButton { background-color:#6C63FF; color:white; border-radius:8px; padding:5px; }"
        "QLineEdit, QSpinBox { background:white; border-radius:5px; }"
        "QTableWidget { background-color: rgba(255,255,255,220); }"
        );
    ui->tab_5->setStyleSheet(
        "QWidget#tab_5 {"
        "border-image: url(C:/Users/admin/Downloads/Telegram Desktop/photo_2026-06-18_12-54-31.jpg);"
        "}"
        "QPushButton { background-color: #6C63FF; color: white; border-radius: 8px; }"
        "QLineEdit, QSpinBox { background-color: white; }"
        "QTableWidget { background-color: rgba(255,255,255,220); }"
        );
    ui->tab_7->setStyleSheet(
        "background-image: url(C:/Users/admin/Pictures/Screenshots/Screenshot 2026-06-18 003102.png);"
        "background-repeat: no-repeat;"
        "background-position: center;"
        );

    ui->tableWidget_search->setColumnCount(5);//construct table of 5 columns
    ui->tableWidget_search->setHorizontalHeaderLabels({"Name", "Age", "ID", "Room", "Year"});

    ui->tableWidget_students->setColumnCount(5);
    ui->tableWidget_students->setHorizontalHeaderLabels({"Name", "Age", "ID", "Room", "Year"});

    ui->tableWidget_rooms->setColumnCount(6);
    ui->tableWidget_rooms->setHorizontalHeaderLabels(
        {"Room", "Students", "Capacity", "Occupied", "Free", "Status"});
    ui->tableWidget_rooms->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_dorms->setColumnCount(3);
    ui->tableWidget_dorms->setHorizontalHeaderLabels({"Dorm Name", "Capacity", "Restaurant"});
    ui->tableWidget_dorms->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->listWidget->clear();

    loadRoomsFromFile();
    loadDormsFromFile();
    loadStudentsFromFile();
}

MainWindow::~MainWindow()
{
    saveRoomsToFile();
    saveDormsToFile();
    saveStudentsToFile();
    delete ui;
}

void MainWindow::on_btn_viewRestaurant_clicked()
{
    int row = ui->tableWidget_dorms->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Select a dorm first.");
        return;
    }
    ui->tabWidget->setCurrentIndex(5);
    ui->comboBox_selectDorm->setCurrentIndex(row);
}

int MainWindow::getRoomNumberFromInput()
{
    QString text = ui->lineEdit_roomNumber->text().trimmed();
    QString digitsOnly = "";
    for (QChar c : text)
        if (c.isDigit()) digitsOnly += c;
    return digitsOnly.toInt();
}

int MainWindow::capacityFromComboBox()
{
    QString t = ui->comboBox->currentText();
    if (t == "Single") return 1;
    if (t == "Double") return 2;
    if (t == "Triple") return 3;
    return ui->spinBox_roomCapacity->value();
}

void MainWindow::on_btn_showStats_clicked()
{
    int totalRooms = rooms.size();
    int totalStudents = ui->tableWidget_students->rowCount();
    int fullRooms = 0;
    int availableRooms = 0;
    int occupiedBeds = 0;
    int freeBeds = 0;

    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i].getStatus() == "Full")
            fullRooms++;
        else
            availableRooms++;

        occupiedBeds += rooms[i].getOccupied();
        freeBeds += rooms[i].getFreeSpots();
    }

    ui->label_totalStudents->setText("Total Students: " + QString::number(totalStudents));
    ui->label_totalRooms->setText("Total Rooms: " + QString::number(totalRooms));
    ui->label_fullRooms->setText("Full Rooms: " + QString::number(fullRooms));
    ui->label_availableRooms->setText("Available Rooms: " + QString::number(availableRooms));
    ui->label_occupiedBeds->setText("Occupied Beds: " + QString::number(occupiedBeds));
    ui->label_freeBeds->setText("Free Beds: " + QString::number(freeBeds));
}

void MainWindow::on_btn_displayStudents_clicked()
{
    ui->tableWidget_search->setRowCount(0);

    for (int i = 0; i < ui->tableWidget_students->rowCount(); i++) {
        QString name = ui->tableWidget_students->item(i,0)->text();
        QString age  = ui->tableWidget_students->item(i,1)->text();
        QString id   = ui->tableWidget_students->item(i,2)->text();
        QString room = ui->tableWidget_students->item(i,3)->text();
        QString year = ui->tableWidget_students->item(i,4)->text();

        int row = ui->tableWidget_search->rowCount();
        ui->tableWidget_search->insertRow(row);
        ui->tableWidget_search->setItem(row,0,new QTableWidgetItem(name));
        ui->tableWidget_search->setItem(row,1,new QTableWidgetItem(age));
        ui->tableWidget_search->setItem(row,2,new QTableWidgetItem(id));
        ui->tableWidget_search->setItem(row,3,new QTableWidgetItem(room));
        ui->tableWidget_search->setItem(row,4,new QTableWidgetItem(year));
    }
}

void MainWindow::on_btn_clearStats_clicked()
{
    ui->label_totalStudents->setText("Total Students: -");
    ui->label_totalRooms->setText("Total Rooms: -");
    ui->label_fullRooms->setText("Full Rooms: -");
    ui->label_availableRooms->setText("Available Rooms: -");
    ui->label_occupiedBeds->setText("Occupied Beds: -");
    ui->label_freeBeds->setText("Free Beds: -");
}

void MainWindow::on_btn_search_clicked()
{
    QString key = ui->lineEdit_search->text().trimmed();
    if (key.isEmpty()) {
        QMessageBox::warning(this, "Search", "Enter name or ID");
        return;
    }

    ui->tableWidget_search->setRowCount(0);

    for (int i = 0; i < ui->tableWidget_students->rowCount(); i++) {
        QString name = ui->tableWidget_students->item(i,0)->text();
        QString age  = ui->tableWidget_students->item(i,1)->text();
        QString id   = ui->tableWidget_students->item(i,2)->text();
        QString room = ui->tableWidget_students->item(i,3)->text();
        QString year = ui->tableWidget_students->item(i,4)->text();

        if (name.contains(key, Qt::CaseInsensitive) || id.contains(key, Qt::CaseInsensitive)) {
            int row = ui->tableWidget_search->rowCount();
            ui->tableWidget_search->insertRow(row);
            ui->tableWidget_search->setItem(row,0,new QTableWidgetItem(name));
            ui->tableWidget_search->setItem(row,1,new QTableWidgetItem(age));
            ui->tableWidget_search->setItem(row,2,new QTableWidgetItem(id));
            ui->tableWidget_search->setItem(row,3,new QTableWidgetItem(room));
            ui->tableWidget_search->setItem(row,4,new QTableWidgetItem(year));
        }
    }
}

void MainWindow::on_btn_addStudent_clicked()
{
    QString name = ui->lineEdit_name->text().trimmed();
    QString id = ui->lineEdit_id->text().trimmed();
    int roomNumber = ui->spinBox_room->value();
    int age = ui->spinBox_age->value();
    int academicYear = ui->spinBox_academicYear->value();

    if (name.isEmpty() || id.isEmpty()) {
        QMessageBox::warning(this, "Missing Data", "Please enter student name and ID.");
        return;
    }

    bool roomFound = false;

    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i].getNumber() == roomNumber) {
            roomFound = true;
            try {
                rooms[i].addStudent(name);
            }
            catch (const std::exception& e) {
                QMessageBox::warning(this, "Room Full", e.what());
                return;
            }
            break;
        }
    }

    if (!roomFound) {
        QMessageBox::warning(this, "Room Not Found", "Room number does not exist.");
        return;
    }

    int row = ui->tableWidget_students->rowCount();
    ui->tableWidget_students->insertRow(row);
    ui->tableWidget_students->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidget_students->setItem(row, 1, new QTableWidgetItem(QString::number(age)));
    ui->tableWidget_students->setItem(row, 2, new QTableWidgetItem(id));
    ui->tableWidget_students->setItem(row, 3, new QTableWidgetItem(QString::number(roomNumber)));
    ui->tableWidget_students->setItem(row, 4, new QTableWidgetItem(QString::number(academicYear)));

    refreshRoomsTable();

    ui->lineEdit_name->clear();
    ui->lineEdit_id->clear();
    ui->spinBox_age->setValue(0);
    ui->spinBox_room->setValue(0);
    ui->spinBox_academicYear->setValue(0);

    QMessageBox::information(this, "Success", "Student added successfully!");
}

void MainWindow::on_btn_deleteStudent_clicked()
{
    int row = ui->tableWidget_students->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Select student");
        return;
    }

    QString studentName = ui->tableWidget_students->item(row, 0)->text();
    int roomNum = ui->tableWidget_students->item(row, 3)->text().toInt();

    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i].getNumber() == roomNum) {
            rooms[i].removeStudent(studentName);
            break;
        }
    }

    ui->tableWidget_students->removeRow(row);
    refreshRoomsTable();
}

void MainWindow::on_btn_addRoom_clicked()
{
    if (dormitories.isEmpty()) {
        QMessageBox::warning(this, "Error", "Add a dormitory first.");
        return;
    }

    int number = getRoomNumberFromInput();
    int cap = capacityFromComboBox();

    if (number <= 0) {
        QMessageBox::warning(this, "Error", "Invalid room number.");
        return;
    }

    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i].getNumber() == number) {
            QMessageBox::warning(this, "Duplicate", "Room already exists.");
            return;
        }
    }

    Room newRoom(number, cap);
    rooms.append(newRoom);
    refreshRoomsTable();

    QString message;
    QTextStream stream(&message);
    stream << newRoom;

    QMessageBox::information(this, "Success", message);
    ui->lineEdit_roomNumber->clear();
}
void MainWindow::on_btn_deleteRoom_clicked()
{
    int number = getRoomNumberFromInput();
    if (number <= 0) {
        QMessageBox::warning(this, "Error", "Invalid room number.");
        return;
    }

    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i].getNumber() == number) {
            rooms.removeAt(i);
            refreshRoomsTable();
            QMessageBox::information(this, "Deleted", "Room deleted successfully.");
            ui->lineEdit_roomNumber->clear();
            return;
        }
    }

    QMessageBox::warning(this, "Error", "Room not found.");
}

void MainWindow::on_btn_updateRoom_clicked()
{
    int number = getRoomNumberFromInput();
    int cap = capacityFromComboBox();

    if (number <= 0) {
        QMessageBox::warning(this, "Error", "Invalid room number.");
        return;
    }

    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i].getNumber() == number) {
            rooms[i].setCapacity(cap);
            refreshRoomsTable();
            QMessageBox::information(this, "Updated", "Room updated successfully.");
            return;
        }
    }

    QMessageBox::warning(this, "Error", "Room not found.");
}

void MainWindow::refreshRoomsTable()
{
    ui->tableWidget_rooms->setRowCount(rooms.size());

    for (int i = 0; i < rooms.size(); i++) {
        ui->tableWidget_rooms->setItem(i,0, new QTableWidgetItem(QString::number(rooms[i].getNumber())));
        ui->tableWidget_rooms->setItem(i,1, new QTableWidgetItem(rooms[i].getStudentsList()));
        ui->tableWidget_rooms->setItem(i,2, new QTableWidgetItem(QString::number(rooms[i].getCapacity())));
        ui->tableWidget_rooms->setItem(i,3, new QTableWidgetItem(QString::number(rooms[i].getOccupied())));
        ui->tableWidget_rooms->setItem(i,4, new QTableWidgetItem(QString::number(rooms[i].getFreeSpots())));

        QTableWidgetItem* statusItem = new QTableWidgetItem(rooms[i].getStatus());
        statusItem->setTextAlignment(Qt::AlignCenter);

        if (rooms[i].getStatus() == "Full")
            statusItem->setForeground(QColor("#e74c3c"));
        else if (rooms[i].getStatus() == "Available")
            statusItem->setForeground(QColor("#27ae60"));
        else
            statusItem->setForeground(QColor("#f39c12"));

        ui->tableWidget_rooms->setItem(i,5, statusItem);
    }
}

void MainWindow::on_btn_addDorm_clicked()
{
    QString name = ui->lineEdit_dormName->text().trimmed();
    int cap = ui->spinBox_capacity->value();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter dormitory name.");
        return;
    }

    dormitories.append(Dormitory(name, cap));

    int row = ui->tableWidget_dorms->rowCount();
    ui->tableWidget_dorms->insertRow(row);
    ui->tableWidget_dorms->setItem(row,0,new QTableWidgetItem(name));
    ui->tableWidget_dorms->setItem(row,1,new QTableWidgetItem(QString::number(cap)));
    ui->tableWidget_dorms->setItem(row,2,new QTableWidgetItem(name + " Restaurant"));

    ui->comboBox_selectDorm->addItem(name);

    ui->lineEdit_dormName->clear();
    ui->spinBox_capacity->setValue(0);

    QMessageBox::information(this, "Success", name + " added with its own Restaurant!");
}

void MainWindow::on_btn_deleteDorm_clicked()
{
    int row = ui->tableWidget_dorms->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Select a dorm first.");
        return;
    }

    dormitories.removeAt(row);
    ui->tableWidget_dorms->removeRow(row);
    ui->comboBox_selectDorm->removeItem(row);

    QMessageBox::information(this, "Deleted", "Dorm deleted successfully.");
}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidget->clear();
    int day = ui->spinBox_day->value();

    QString meal;
    if (ui->radio_breakfast->isChecked())      meal = "Breakfast";
    else if (ui->radio_lunch->isChecked())     meal = "Lunch";
    else if (ui->radio_dinner->isChecked())    meal = "Dinner";
    else {
        QMessageBox::warning(this, "Error", "Select meal first");
        return;
    }

    QVector<QVector<QString>> breakfastMenu = {
        {"🥐 Bread", "🥛 Milk"}, {"🍳 Eggs", "🍞 Toast"},
        {"🥞 Pancakes", "🍵 Tea"}, {"🥖 Baguette", "☕ Coffee"},
        {"🍪 Cookies", "🥛 Milk"}, {"🍩 Donuts", "🍵 Tea"},
        {"🥐 Croissant", "🍊 Juice"}
    };

    QVector<QVector<QString>> lunchMenu = {
        {"🍗 Chicken", "🍚 Rice"}, {"🍝 Pasta", "🥗 Salad"},
        {"🍔 Burger", "🍟 Fries"}, {"🍕 Pizza", "🥤 Juice"},
        {"🍲 Soup", "🍞 Bread"}, {"🥩 Steak", "🥗 Salad"},
        {"🍛 Couscous", "🍖 Meat"}
    };

    QVector<QVector<QString>> dinnerMenu = {
        {"🥔 Potatoes", "🍎 Fruit"}, {"🥪 Sandwich", "🍵 Tea"},
        {"🍝 Light Pasta", "🥗 Salad"}, {"🍲 Soup", "🍞 Bread"},
        {"🍗 Chicken", "🥤 Juice"}, {"🍳 Omelette", "🍵 Tea"},
        {"🥗 Salad", "🍎 Fruit"}
    };

    QVector<QString> selectedMenu;
    if (meal == "Breakfast") selectedMenu = breakfastMenu[day - 1];
    else if (meal == "Lunch") selectedMenu = lunchMenu[day - 1];
    else selectedMenu = dinnerMenu[day - 1];

    for (const QString& item : selectedMenu)
        ui->listWidget->addItem(item);

    QMessageBox::information(this, "Done", QString("Day %1 - %2 menu loaded").arg(day).arg(meal));
}

// =======================================================
// SAVE / LOAD — DATA PERSISTENCE
// =======================================================

void MainWindow::saveRoomsToFile()
{
    QFile file("rooms.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save rooms file.");
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < rooms.size(); i++) {
        out << rooms[i].getNumber() << ","
            << rooms[i].getCapacity() << ","
            << rooms[i].getOccupied() << ","
            << rooms[i].getStudentsList() << "\n";
    }

    file.close();
}

void MainWindow::loadRoomsFromFile()
{
    QFile file("rooms.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    rooms.clear();
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() >= 3) {
            int number = parts[0].toInt();
            int capacity = parts[1].toInt();

            Room r(number, capacity);

            if (parts.size() >= 4 && !parts[3].isEmpty()) {
                QStringList studentNames = parts[3].split(", ");
                for (const QString& name : studentNames) {
                    try {
                        r.addStudent(name);
                    } catch (...) {}
                }
            }

            rooms.append(r);
        }
    }

    file.close();
    refreshRoomsTable();
}

void MainWindow::saveDormsToFile()
{
    QFile file("dorms.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save dorms file.");
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < dormitories.size(); i++) {
        out << dormitories[i].getName() << ","
            << dormitories[i].getCapacity() << "\n";
    }

    file.close();
}

void MainWindow::loadDormsFromFile()
{
    QFile file("dorms.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    dormitories.clear();
    ui->tableWidget_dorms->setRowCount(0);
    ui->comboBox_selectDorm->clear();

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() >= 2) {
            QString name = parts[0];
            int cap = parts[1].toInt();

            dormitories.append(Dormitory(name, cap));

            int row = ui->tableWidget_dorms->rowCount();
            ui->tableWidget_dorms->insertRow(row);
            ui->tableWidget_dorms->setItem(row, 0, new QTableWidgetItem(name));
            ui->tableWidget_dorms->setItem(row, 1, new QTableWidgetItem(QString::number(cap)));
            ui->tableWidget_dorms->setItem(row, 2, new QTableWidgetItem(name + " Restaurant"));

            ui->comboBox_selectDorm->addItem(name);
        }
    }

    file.close();
}

void MainWindow::saveStudentsToFile()
{
    QFile file("students.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save students file.");
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < ui->tableWidget_students->rowCount(); i++) {
        QString name = ui->tableWidget_students->item(i, 0)->text();
        QString age  = ui->tableWidget_students->item(i, 1)->text();
        QString id   = ui->tableWidget_students->item(i, 2)->text();
        QString room = ui->tableWidget_students->item(i, 3)->text();
        QString year = ui->tableWidget_students->item(i, 4)->text();

        out << name << "," << age << "," << id << "," << room << "," << year << "\n";
    }

    file.close();
}

void MainWindow::loadStudentsFromFile()
{
    QFile file("students.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    ui->tableWidget_students->setRowCount(0);
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() >= 5) {
            int row = ui->tableWidget_students->rowCount();
            ui->tableWidget_students->insertRow(row);
            ui->tableWidget_students->setItem(row, 0, new QTableWidgetItem(parts[0]));
            ui->tableWidget_students->setItem(row, 1, new QTableWidgetItem(parts[1]));
            ui->tableWidget_students->setItem(row, 2, new QTableWidgetItem(parts[2]));
            ui->tableWidget_students->setItem(row, 3, new QTableWidgetItem(parts[3]));
            ui->tableWidget_students->setItem(row, 4, new QTableWidgetItem(parts[4]));
        }
    }

    file.close();
}

void MainWindow::on_btn_saveData_clicked()
{
    saveRoomsToFile();
    saveDormsToFile();
    saveStudentsToFile();
    QMessageBox::information(this, "Saved", "All data saved successfully!");
}

void MainWindow::on_btn_loadData_clicked()
{
    loadRoomsFromFile();
    loadDormsFromFile();
    loadStudentsFromFile();
    QMessageBox::information(this, "Loaded", "All data loaded successfully!");
}