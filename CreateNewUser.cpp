#include "CreateNewUser.h"

CreateNewUser::CreateNewUser(QWidget* parent): QDialog (parent)
{
    QGridLayout*    layuot = new QGridLayout(this);
    QLabel*         lbl_user = new QLabel("ФИО");
    QLabel*         lbl_Login = new QLabel("Логин");
    QLabel*         lbl_Password = new QLabel("Пароль");
    QLabel*         lbl_possition = new QLabel("Должность");
    QPushButton*    btn_createNewUser = new QPushButton("Зарегистрироваться");
    QStringList     work_possition{"Работник","Ветеринарный врач","Стажер","Техник"};

    ledit_Login = new QLineEdit;
    ledit_Password = new QLineEdit;
    ledit_NewUser = new QLineEdit;
    cmbbox_possition = new QComboBox;
    cmbbox_possition->addItems(work_possition);

    layuot->addWidget(lbl_user,0,0);
    layuot->addWidget(ledit_NewUser,0,1);
    layuot->addWidget(lbl_possition,1,0);
    layuot->addWidget(cmbbox_possition,1,1);
    layuot->addWidget(lbl_Login,2,0);
    layuot->addWidget(ledit_Login,2,1);
    layuot->addWidget(lbl_Password,3,0);
    layuot->addWidget(ledit_Password,3,1);
    layuot->addWidget(btn_createNewUser,4,1);

    connect(btn_createNewUser,SIGNAL(clicked()),this,SLOT(slot_createNewUser()));
}



QString CreateNewUser::login()
{
    return ledit_Login->text();
}

QString CreateNewUser::password()
{
    return ledit_Password->text();
}

QString CreateNewUser::userName()
{
    return ledit_NewUser->text();
}

QString CreateNewUser::possition()
{
    return cmbbox_possition ->currentText();
}

void CreateNewUser::slot_createNewUser()
{
   emit signal_saveNewUser(userName(),possition(),login(),password());
   close();
}

void CreateNewUser::slot_showWindow()
{
    show();
}

void CreateNewUser::slot_closeWindow()
{
    close();
}
