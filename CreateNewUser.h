#ifndef CREATE_NEW_USER_H
#define CREATE_NEW_USER_H

#include <QtWidgets>
#include <QDialog>

class CreateNewUser:  public QDialog
{
    Q_OBJECT
public:
    CreateNewUser(QWidget* parent = 0);

    QString login();
    QString password();
    QString userName();
    QString possition();

public slots:
    void slot_createNewUser();
    void slot_showWindow();
    void slot_closeWindow();

private:
    QLineEdit*   ledit_Login;
    QLineEdit*   ledit_Password;
    QLineEdit*   ledit_NewUser;
    QComboBox*   cmbbox_possition;

signals:
    void signal_saveNewUser(QString userName,QString login, QString password, QString possition);
};

#endif // CREATE_NEW_USER_H
