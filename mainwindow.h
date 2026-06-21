#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include "room.h"
#include "student.h"
#include "dormitory.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_addStudent_clicked();
    void on_btn_deleteStudent_clicked();
    void on_btn_search_clicked();
    void on_btn_addRoom_clicked();
    void on_btn_deleteRoom_clicked();
    void on_btn_updateRoom_clicked();
    void on_btn_addDorm_clicked();
    void on_btn_deleteDorm_clicked();

private slots:
    void on_btn_showStats_clicked();
    void on_btn_clearStats_clicked();
    void on_btn_viewRestaurant_clicked();
    void on_pushButton_clicked();
    void on_btn_displayStudents_clicked();
    void on_btn_saveData_clicked();
    void on_btn_loadData_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Room> rooms;
    QVector<Student> students;
    QVector<Dormitory> dormitories;

    void refreshRoomsTable();
    int capacityFromComboBox();
    int getRoomNumberFromInput();

    void saveRoomsToFile();
    void loadRoomsFromFile();
    void saveDormsToFile();
    void loadDormsFromFile();
    void saveStudentsToFile();
    void loadStudentsFromFile();
};

#endif