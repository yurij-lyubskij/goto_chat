#include "login_window.h"
#include "./ui_login_window.h"

Login_window::Login_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login_window)
{
    ui->setupUi(this);
}

Login_window::~Login_window()
{
    delete ui;
}

bool Login_window::local_check_person(const QString &login, const QString &password)
{
    return true;
}

bool Login_window::check_person(const QString &login, const QString &password)
{
    return true;
}

