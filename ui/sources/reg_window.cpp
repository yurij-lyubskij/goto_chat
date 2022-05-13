#include "reg_window.h"
#include "ui_reg_window.h"

Reg_window::Reg_window(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Reg_window) {
    ui->setupUi(this);
}

Reg_window::~Reg_window() {
    delete ui;
}

void Reg_window::registrate() {

}

bool Reg_window::check_data() {
    return true;
}

void Reg_window::on_pushButton_clicked() {
    clear_lines();
    this->close();
    emit login_window();
}


void Reg_window::on_checkBox_2_stateChanged(int) {
    if (ui->checkBox_2->isChecked()) {
        ui->lineEdit_5->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_5->setEchoMode(QLineEdit::Password);
    }
}


void Reg_window::on_checkBox_stateChanged(int) {
    if (ui->checkBox->isChecked()) {
        ui->lineEdit_6->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_6->setEchoMode(QLineEdit::Password);
    }
}


void Reg_window::on_pushButton_2_clicked() {
    bool f_name = Checker::check_name(ui->lineEdit->text().toStdString());
    bool f_second_name = Checker::check_name(ui->lineEdit_2->text().toStdString());
    bool f_email = Checker::check_email(ui->lineEdit_3->text().toStdString());
    bool f_login = Checker::check_login(ui->lineEdit_4->text().toStdString());
    bool f_password = Checker::check_password(ui->lineEdit_5->text().toStdString());

    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty()
        || ui->lineEdit_4->text().isEmpty() || ui->lineEdit_5->text().isEmpty() || ui->lineEdit_6->text().isEmpty()) {
        ui->error_label->setText("Вы заполните не все поля");
        return;
    }
    if (!f_name || !f_second_name) {
        ui->error_label->setText("Неверный формат имени или фамилии.\nПожалуйста заполните эти поля корректно");
        return;
    }
    if (!f_email) {
        ui->error_label->setText("Неверный формат email");
        return;
    }
    if (!f_login) {
        ui->error_label->setText("Неверный формат логина");
        return;
    }
    if (!f_password) {
        ui->error_label->setText("Неверный формат пароля");
        return;
    }
    if (ui->lineEdit_5->text() != ui->lineEdit_6->text()) {
        ui->error_label->setText("Пароли не совпадают");
        return;
    }

    on_pushButton_clicked();
}

void Reg_window::centrialize() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height() - this->height();
    int width = screenGeometry.width() - this->width();
    this->setGeometry(width / 2, height / 2, this->width(), this->height());
}

void Reg_window::clear_lines() {
    ui->error_label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
}

