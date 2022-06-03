#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QtWidgets>
#include <QDialog>
#include <QMessageBox>
#include "CreateNewUser.h"


class LoginWindow:  public QDialog
{
    Q_OBJECT
public:
    LoginWindow(QWidget* parent = 0 );
    ~LoginWindow();

    QString login();
    QString password();



public slots:
    void slot_btn_enter();
    void slot_close_window();
    void slot_newUser();
    void slot_show_window();
    void slot_show_password();
    void slot_forgot_password();

private:
    QLineEdit*   ledit_Login;
    QLineEdit*   ledit_Password;

    QLineEdit* ledit_NewLogin;
    QLineEdit* ledit_NewPassword;
    QLineEdit* ledit_NewUser;

    QAction *show_password;
    QIcon hide_icon;
    QIcon show_icon;



signals:
    void user_want_enter(QString login, QString password);
    void signal_createNewUser();
};

#endif // LOGINWINDOW_H
