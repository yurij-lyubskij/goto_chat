#include "login_window.h"
#include "./ui_login_window.h"
#include <QApplication>

Login_window::Login_window(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::Login_window) {
    ui->setupUi(this);
    centrialize();
    cl = std::shared_ptr<Client>(new Client());

    reg_window = new Reg_window();
    app_window = new App_window();
    connect(reg_window, &Reg_window::login_window, this, &Login_window::show);
    connect(reg_window, &Reg_window::login_window, this, &Login_window::centrialize);
    connect(this, &Login_window::window_location, reg_window, &Reg_window::centrialize);

    connect(this, &Login_window::send_person, app_window, &App_window::set_person);
    connect(app_window, &App_window::login_window, this, &Login_window::show);
    connect(this, &Login_window::window_location, app_window, &App_window::centrialize);
    connect(app_window, &App_window::login_window, this, &Login_window::centrialize);
}

Login_window::~Login_window() {
    delete ui;
}


// проверить логин и пароль челика
bool Login_window::check_person(const QString &login, const QString &password) {
    return true;
}


void Login_window::on_checkBox_stateChanged(int) {
    if (ui->checkBox->isChecked()) {
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}


// кнопка войти в приложение
void Login_window::on_enter_button_clicked() {
    std::string log = ui->lineEdit->text().toStdString();
    std::string password = ui->lineEdit_2->text().toStdString();
    if (!Checker::check_phone(log) || !Checker::check_password(password)) {
        ui->error_message->setText("Некорректный формат введенных данных");
        return;
    }
    if (cl->sign_in(log, password)) {
        emit send_person(ui->lineEdit->text(), cl);
        emit window_location();
        app_window->show();
        hide();
    } else {
        ui->error_message->setText("Неверный телефон или пароль");
    }
    // закоментировать то что ниже когда поключение к серверу
//    emit send_person(ui->lineEdit->text(), cl);
//    emit window_location();
//    app_window->show();
//    hide();
}


// нажатие на кнопку зарегистрироваться
void Login_window::on_reg_button_clicked() {
    emit window_location();
    hide();
    reg_window->show();
    clear_lines();
}


void Login_window::centrialize() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height() - this->height();
    int width = screenGeometry.width() - this->width();
    this->setGeometry(width / 2, height / 2, this->width(), this->height());
}

void Login_window::clear_lines() {
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->error_message->clear();
}

