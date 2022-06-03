#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString col_name;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/tdavidyuk/mini_zoo.sqlite");
    if(!db.open()){
        QMessageBox::critical(this,"Ошибка","Невозможно открыть базу данных: " + db.lastError().text());
        return;
    }

// ВКЛАДКА С РАСПИСАНИЕМ
    model_timetable = new QSqlTableModel(this,db);
    model_timetable->setTable("tasks");
    if( model_timetable->columnCount() > 0){
        for( int i = 0; i < model_timetable->columnCount(); i++){
            col_name = model_timetable->headerData(i,Qt::Orientation::Horizontal).toString();
            if(col_name == "time")
                model_timetable->setHeaderData(i,Qt::Horizontal,"Время");
            if(col_name == "task")
                model_timetable->setHeaderData(i,Qt::Horizontal,"Задача");
            if(col_name == "comment")
                model_timetable->setHeaderData(i,Qt::Horizontal,"Примечания");
        }
    }
    ui->tableView_timetable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_timetable->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_timetable->setAlternatingRowColors(true);
    ui->tableView_timetable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->tableView_timetable->setModel(model_timetable);
    ui->tableView_timetable->hideColumn(0); // скрыть id
    ui->tableView_timetable->hideColumn(1); // скрыть дату
    p_NotEditableDelegate = new NotEditableDelegate;
    ui->tableView_timetable->setItemDelegateForColumn(2,p_NotEditableDelegate); //запретить редактирование времени и задачи
    ui->tableView_timetable->setItemDelegateForColumn(3,p_NotEditableDelegate);


    ui->btn_load_timetable->setIcon(QIcon(":/images/download.png"));
    ui->btn_print->setIcon(QIcon(":/images/printer.png"));
    ui->lineEdit_date->setPlaceholderText("дд.мм.гггг");
    ui->frame_3->setStyleSheet("QFrame{background-color:#d5eddc;}");
    ui->frame->setStyleSheet("QFrame{background-color:#d5eddc;}");
    ui->frame_2->setStyleSheet("QFrame{background-color:#d5eddc;}");
    setWindowIcon(QIcon("/home/tdavidyuk/Develop/ex/taskmanager/icon1.png"));
    setWindowTitle("Электронный журнал");

   QObject::connect(&logWindow, SIGNAL( user_want_enter(QString, QString)), this, SLOT(slot_user_authorization(QString, QString)));
   QObject::connect(this,SIGNAL(close_window()),&logWindow, SLOT(slot_close_window()));
   QObject::connect(ui->lineEdit_date,SIGNAL(returnPressed()),SLOT(on_btn_load_timetable_clicked()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: slot_user_authorization(QString login, QString password)
{
    QSqlQuery   query;
    QSqlRecord  rec_check;
    if( !query.exec("SELECT id,name FROM workers WHERE login='"+login + "' and password='" + password +"';")){
        QMessageBox::critical(this,"Ошибка", "Неверный запрос в БД");
        return;
    }
    rec_check = query.record();
    if(!query.next()){
        QMessageBox::critical(this,"Ошибка", "Неверный логин или пароль.");
        return;
    }
    worker = query.value(1).toString();
    ui->label_operators->setText("Привет, "+worker +"!");
    emit close_window();
    show();
}



void MainWindow::slot_createUser(QString name,QString possition, QString login, QString password)
{
    QSqlQuery   query;
    if( name.size() == 0 || login.size() == 0 || password.size() == 0 || possition.size() == 0){
        QMessageBox:: warning(this,"Ошибка","Заполните пустые поля!");
        return;
    }
    query.prepare("INSERT INTO workers (name,possition,login,password) VALUES(\"" + name + "\",\"" + possition +"\",\""+ login +"\",\""+ password+"\");" );
    if(!query.exec()){
        QMessageBox:: warning(this,"error",query.lastError().text());
        return;
    }
    else {
        emit close_userWindow();
        QMessageBox::information(this,"","Пользователь "+ name +" создан!");
    }
}

void MainWindow::on_btn_addUser_clicked()
{
    logWindow.show();
    logWindow.setWindowTitle("Авторизация");
}

//ВКЛАДКА С РАСПИСАНИЕМ
void MainWindow::on_btn_load_timetable_clicked()
{
    QString date = ui->lineEdit_date->text();
    model_timetable->setFilter("date='"+ date+"'");
    model_timetable->select();
}

void MainWindow::on_btn_print_clicked()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setOutputFileName("table.pdf");
    printer.setPaperSize(QPrinter::A4);
    printer.setPageMargins(QMarginsF(20, 15, 10, 20));
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Document"));

    QString html;
    const QString format("<td align=\"center\" style=\"padding:3px;font-size:14px; border-spacing: 1px;font-family:'Times New Roman';\">%1</td>");
    const QString format_header("<td align=\"center\" style=\"padding:3px;font-size:14px;font-weight:bold;font-family:'Times New Roman';\">%1</td>");
    const QString format_comment("<td style=\"padding:3px;font-size:14px; border-spacing: 1px;font-family:'Times New Roman';\">%1</td>");
    QString date = ui->tableView_timetable->model()->data(ui->tableView_timetable->model()->index(0,1),Qt::DisplayRole).toString();
    html = "<!DOCTYPE html><html><body>";
    html += "<table border=\"0\"><tr>";
    html += format_header.arg("Начало смены:");
    html += format.arg(date);
    html += format.arg("08:00");
    html += format_header.arg("Конец смены:");
    html += format.arg(" ");
    html += "</tr></table><br>";
    html += "<table border=\"0.3\"><tr>";
    html += format_header.arg("№");
    html += format_header.arg("Время");
    html += format_header.arg("Задача");
    html += format_header.arg("Примечание");
    html += "</tr>";
    for(int i = 0; i < ui->tableView_timetable->model()->rowCount(); i++){
        html += "<tr>" + format.arg(QString::number(i + 1));
        QString time = ui->tableView_timetable->model()->data(ui->tableView_timetable->model()->index(i,2),Qt::DisplayRole).toString();
        html += format.arg(time);
        QString task = ui->tableView_timetable->model()->data(ui->tableView_timetable->model()->index(i,3),Qt::DisplayRole).toString();
        html += format.arg(task);
        html += format_comment.arg(ui->tableView_timetable->model()->data(ui->tableView_timetable->model()->index(i,4),Qt::DisplayRole).toString());
        html += "</tr>";
    }
    html += "</table><br>";
    html += "<table border =\"0\"><tr><td style=\"padding:3px;font-size:14px;font-weight:bold;font-family:'Times New Roman';\" >Сотрудник:</td>";
    html += "<td style=\"padding:3px;font-size:14px;font-family:'Times New Roman';\">" + worker+"</td><td>  ___________</td></tr><tr></tr>";
    html += "</table></body></html>";

    if (dialog->exec() != QDialog::Accepted)
        return;
    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);
}





