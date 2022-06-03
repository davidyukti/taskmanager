#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginWindow login_window;
    CreateNewUser newUser_window;
    login_window.show();
    QObject::connect(&login_window, SIGNAL( user_want_enter(QString, QString)), &w, SLOT(slot_user_authorization(QString, QString)));
    QObject::connect(&w,SIGNAL(close_window()),&login_window, SLOT(slot_close_window()));
    QObject::connect(&w,SIGNAL(show_window()),&login_window, SLOT(show_close_window()));
    QObject::connect(&login_window,SIGNAL(signal_createNewUser()),&newUser_window,SLOT(slot_showWindow()));
    QObject::connect(&newUser_window,SIGNAL(signal_saveNewUser(QString,QString,QString,QString)),&w,SLOT(slot_createUser(QString,QString, QString,QString)));
    QObject::connect(&w,SIGNAL(close_userWindow()),&newUser_window,SLOT(slot_closeWindow()));

    login_window.setWindowTitle("Авторизация");
    newUser_window.setWindowTitle("Регистрация");
    QFile file_CSS(":/style/style.css");
    file_CSS.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file_CSS.readAll());
    qApp->setStyleSheet(strCSS);


    return a.exec();
}
