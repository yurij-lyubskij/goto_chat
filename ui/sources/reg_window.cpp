#include "reg_window.h"
#include "ui_reg_window.h"

Reg_window::Reg_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reg_window)
{
    ui->setupUi(this);
}

Reg_window::~Reg_window()
{
    delete ui;
}

void Reg_window::registrate()
{

}

bool Reg_window::check_data()
{
    return true;
}
