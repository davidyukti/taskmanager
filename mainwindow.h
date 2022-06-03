#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QSqlTableModel>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include "NotEditableDelegate.h"
#include "LoginWindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow          *ui;
    QSqlDatabase            db;
    QSqlTableModel          *model_timetable;
    NotEditableDelegate     *p_NotEditableDelegate;
    LoginWindow             logWindow;
    QString                 worker;


public slots:
    void slot_user_authorization(QString login, QString password);
    void slot_createUser(QString name, QString possition, QString login, QString password);

signals:
    void close_window();
    void show_window();
    void close_userWindow();

private slots:
    void on_btn_load_timetable_clicked();
    void on_btn_print_clicked();
    void on_btn_addUser_clicked();
};

#endif // MAINWINDOW_H
