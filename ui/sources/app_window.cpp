#include "app_window.h"
#include "ui_app_window.h"

App_window::App_window(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::App_window) {
    ui->setupUi(this);
//    ui->chat->setFixedSize(this->width()/2, this->height());
    ui->chats_and_profile->setFixedSize(this->width() / 3, this->height() / 2);
}

App_window::~App_window() {
    delete ui;
}

void App_window::set_person(const QString &Login) {
    login = Login;
    ui->profile->show();
    ui->profile->show();
    ui->chat_list->hide();
    ui->login_label->setText(login);
}


void App_window::on_toolButton_2_clicked() {
    if (ui->toolButton_2->text() == "Профиль") {
        ui->profile->show();
        ui->chat_list->hide();
        ui->toolButton_2->setText("Чаты");
    } else {
        ui->profile->hide();
        ui->chat_list->show();
        ui->toolButton_2->setText("Профиль");
    }
}


void App_window::on_pushButton_3_clicked() {
    emit login_window();
    close();
}

