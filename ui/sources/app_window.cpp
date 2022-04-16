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
