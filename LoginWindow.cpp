#include "LoginWindow.h"

LoginWindow::LoginWindow(QWidget* parent): QDialog (parent)
{
    hide_icon.addPixmap(QPixmap(":/images/hide_password.png"));
    show_icon.addPixmap(QPixmap(":/images/show_password.png"));
    QGridLayout* layout = new QGridLayout;
    QPushButton* btn_Enter = new QPushButton("Вход");
    QPushButton* btn_checkIn = new QPushButton("Регистрация");
    QPushButton* btn_forgot_password = new QPushButton("Забыли пароль?");

    btn_forgot_password->setStyleSheet("QPushButton{background-color:#fff;border:none;color:blue;padding: 3px 3px;"
                                       "font-size: 12px;font-family: inherit;}"
                                       "QPushButton:hover{text-decoration:underline}");
    btn_forgot_password->setCursor(Qt::PointingHandCursor);
    btn_Enter->setCursor(Qt::PointingHandCursor);
    btn_checkIn->setCursor(Qt::PointingHandCursor);

    ledit_Login = new QLineEdit("agapova");
    ledit_Login->setPlaceholderText("Логин");
    ledit_Password = new QLineEdit("123");
    ledit_Password->setPlaceholderText("Пароль");
    ledit_Password->setEchoMode(QLineEdit::Password); //пароль точками
    show_password = ledit_Password->addAction(hide_icon,QLineEdit::TrailingPosition); //показать/скрыть пароль

    layout->addWidget(ledit_Login,0,0,1,2);
    layout->addWidget(ledit_Password,1,0,1,2);
    layout->addWidget(btn_Enter,2,0);
    layout->addWidget(btn_forgot_password,3,0,1,2);
    layout->addWidget(btn_checkIn,2,1);
    setLayout(layout);

    connect(btn_Enter,SIGNAL(clicked()),SLOT(slot_btn_enter()));
    connect(btn_checkIn,SIGNAL(clicked()),SLOT(slot_newUser()));
    connect(btn_forgot_password,SIGNAL(clicked()),SLOT(slot_forgot_password()));
    connect(show_password,SIGNAL(triggered()), SLOT(slot_show_password()));
}

LoginWindow::~LoginWindow()
{

}

void LoginWindow::slot_show_password()
{
    if(ledit_Password->echoMode() == QLineEdit::Password){
        ledit_Password->setEchoMode(QLineEdit::Normal);
        show_password->setIcon(show_icon);
    }
    else{
        ledit_Password->setEchoMode(QLineEdit::Password);
        show_password->setIcon(hide_icon);
    }
}

QString LoginWindow::login()
{
    return ledit_Login->text();
}

QString LoginWindow::password()
{
    return ledit_Password->text();
}

void LoginWindow::slot_btn_enter()
{
    emit user_want_enter(login(),password());
}

void LoginWindow::slot_close_window()
{
    close();
}

void LoginWindow::slot_show_window()
{
    show();
}

void LoginWindow::slot_newUser()
{
   emit signal_createNewUser();
}

void LoginWindow::slot_forgot_password()
{
    QMessageBox::information(this,"Восстановление пароля","Для восстановления пароля обратитесь к системному администратору");
}




