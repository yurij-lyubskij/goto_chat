#include "app_window.h"
#include "ui_app_window.h"
#include <thread>
#include <iostream>

App_window::App_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App_window) {
    ui->setupUi(this);
    //player.setAudioOutput(&audioOutput);
    //    ui->chat->setFixedSize(this->width()/2, this->height());
    //    ui->chats_and_profile->setFixedSize(this->width() / 3, this->height() / 2);
}

App_window::~App_window() {
    delete ui;
}

void App_window::refresh_timer()
{
    while(f){
        ui->statusbar->showMessage(rec.time_duration());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
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



void App_window::on_toolButton_3_pressed()
{
//    player.stop();
//    player.source().clear();
    f = true;


    QString time = QTime::currentTime().toString();
    std::replace_if(time.begin(), time.end(), [](QChar x) {return x == ':' ;}, '_');
    rec.record_audio("gay");
    //    rec.record_audio("voices/" + time);
    std::thread th(&App_window::refresh_timer, this);
    th.detach();
}


void App_window::on_toolButton_3_released()
{
    f = false;
    rec.stop_recording();
}


void App_window::on_pushButton_clicked()
{
    player = std::unique_ptr<QMediaPlayer>(new QMediaPlayer);
    audioOutput = std::shared_ptr<QAudioOutput>(new QAudioOutput);
    player->setAudioOutput(audioOutput.get());
    QString path = "./gay.m4a";
    player->setSource(path);
    player->audioOutput()->setVolume(50);
    player->play();
}

