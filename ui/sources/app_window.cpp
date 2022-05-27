#include "app_window.h"
#include "ui_app_window.h"
#include <thread>
#include <iostream>

App_window::App_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App_window) {
    ui->setupUi(this);
    ui->chat_creation->hide();
    ui->pushButton_5->hide();
    ui->listView->setEditTriggers(QListView::NoEditTriggers);
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
        show_chats();
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

void App_window::centrialize()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height() - this->height();
    int width = screenGeometry.width() - this->width();
    this->setGeometry(width / 2, height / 2, this->width(), this->height());
}



// двойное нажание на название чата
void App_window::on_listView_doubleClicked(const QModelIndex &index)
{
    ui->messages->setTitle(index.data(0).toString());
}


// кнопка создания нового чата
void App_window::on_toolButton_clicked()
{
    ui->pushButton_5->show();
    ui->main_things->hide();
    ui->toolButton_2->hide();
    ui->chat_creation->show();
}


void App_window::on_pushButton_5_clicked()
{
    ui->main_things->show();
    ui->toolButton_2->show();
    ui->chat_creation->hide();
    ui->pushButton_5->hide();
}

void App_window::show_chats()
{
    model = std::unique_ptr<QStringListModel>(new QStringListModel);
    std::vector<Chat> m;
    m.push_back({"1", "rwerwef"});
    m.push_back({"2", "rwerwg3gef"});
    m.push_back({"3", "egerwerwef"});
    QStringList chats;
    for(const auto& mes : m){
        chats.push_back(QString::fromStdString(mes.chatName));
    }
    model.get()->setStringList(chats);
    ui->listView->setModel(model.get());
}

