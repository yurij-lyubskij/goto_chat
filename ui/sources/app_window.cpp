#include "app_window.h"
#include "ui_app_window.h"
#include <thread>
#include <iostream>

App_window::App_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App_window) {
    ui->setupUi(this);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    ui->chat_creation->hide();
    ui->pushButton_5->hide();
    ui->pushButton_7->hide();
    ui->add_person->hide();
    ui->listView->setEditTriggers(QListView::NoEditTriggers);
    ui->listView_2->setEditTriggers(QListView::NoEditTriggers);
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
    ui->chat_list->hide();
    ui->login_label->setText(login);
    show_chats();
}


// кнопка профиль -> чаты(сверху слева)
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


// кнопка выйти из приложения
void App_window::on_pushButton_3_clicked() {
    emit login_window();
    close();
}


// кнопка записи голосового(удерживается)
void App_window::on_toolButton_3_pressed()
{
    f = true;

    QString time = QTime::currentTime().toString();
    std::replace_if(time.begin(), time.end(), [](QChar x) {return x == ':' ;}, '_');
    rec.record_audio("gay");
    //    rec.record_audio("voices/" + time);
    std::thread th(&App_window::refresh_timer, this);
    th.detach();
}

// кнопка записи голосового(отпускается)
void App_window::on_toolButton_3_released()
{
    f = false;
    rec.stop_recording();
}


// кнопка отправить
void App_window::on_pushButton_clicked()
{

}

void App_window::centrialize()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height() - this->height()/2;
    int width = screenGeometry.width() - this->width();
    this->setGeometry(width / 2, height / 2, this->width(), this->height()/2);
}



// двойное нажание на название чата
void App_window::on_listView_doubleClicked(const QModelIndex &index)
{
    QString chat_name = index.data(0).toString();
    ui->messages->setTitle(chat_name);
    show_messages(chat_name);
}


// кнопка создания нового чата
void App_window::on_toolButton_clicked()
{
    ui->pushButton_5->show();
    ui->main_things->hide();
    ui->toolButton_2->hide();
    ui->chat_creation->show();
}

// кнопка назад из создания чата
void App_window::on_pushButton_5_clicked()
{
    ui->main_things->show();
    ui->toolButton_2->show();
    ui->chat_creation->hide();
    ui->pushButton_5->hide();
}

// функция отображения чатов
void App_window::show_chats()
{
    model = std::unique_ptr<QStringListModel>(new QStringListModel);
    std::vector<Chat> m;
    m.push_back({"1", "rwerwef"});
    m.push_back({"2", "rwerwg3gef"});
    m.push_back({"3", "egerwerwef"});
    QStringList chats;
    for(const auto& chat : m){
        chats.push_back(QString::fromStdString(chat.chatName));
    }
    model.get()->setStringList(chats);
    ui->listView->setModel(model.get());
}

// функция отображения сообщений
void App_window::show_messages(const QString &chat_name)
{
    model2 = std::unique_ptr<QStringListModel>(new QStringListModel);
    std::vector<Message> m;
//    Client::get_last_messages(0)
//    m = Parser::messages(...)
    m.push_back({"1", "rwerwef", "+89034", "21:00:11"});
    m.push_back({"2", "gay.m4a", "+94329034", "21:00:12"});
    m.push_back({"3", "egerwerwef", "+3443", "21:00:13"});
    QStringList messages;
    for(const auto& mes : m){
        std::string temp_res = Parser::get_message_from_Message(mes);
        messages.push_back(QString::fromStdString(temp_res));
    }
    model2.get()->setStringList(messages);
    ui->listView_2->setModel(model2.get());
}

// прослушать голосовое по названию файла который скачали/ есть
void App_window::listen_audio(const std::string &file_name)
{
    player = std::unique_ptr<QMediaPlayer>(new QMediaPlayer);
    audioOutput = std::shared_ptr<QAudioOutput>(new QAudioOutput);
    player->setAudioOutput(audioOutput.get());
    QString path = "./" + QString::fromStdString(file_name);
    player->setSource(path);
    player->audioOutput()->setVolume(50);
    player->play();
}


void App_window::on_listView_2_doubleClicked(const QModelIndex &index)
{
    std::string text = Parser::get_text_from_message(index.data(0).toString().toStdString());
    if(text.find(".m4a", 0, 1) < text.size() - 1){
        listen_audio(text);
    }
}


// кнопка найти чат
void App_window::on_pushButton_2_clicked()
{
    QString chat_name = ui->lineEdit_2->text();
}

// кнопка перейти к добавлению человека в чат
void App_window::on_toolButton_4_clicked()
{
    ui->main_things->hide();
    ui->toolButton_2->hide();
    ui->messages->hide();
    ui->add_person->show();
    ui->pushButton_7->show();
}

// кнопка назад из добавления человека
void App_window::on_pushButton_7_clicked()
{
    ui->main_things->show();
    ui->toolButton_2->show();
    ui->messages->show();
    ui->add_person->hide();
    ui->pushButton_7->hide();
}

// кнопка добавить человека в чат
void App_window::on_pushButton_6_clicked()
{

}

