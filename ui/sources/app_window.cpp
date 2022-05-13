#include "app_window.h"
#include "ui_app_window.h"

App_window::App_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App_window)
{
    ui->setupUi(this);
}

App_window::~App_window()
{
    delete ui;
}

void App_window::set_person(const QString &Login)
{
    login = Login;
}

void App_window::on_commandLinkButton_clicked()
{
    ui->label->setText(login);
}

