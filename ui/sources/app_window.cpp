#include "app_window.h"
#include "ui_app_window.h"
#include <thread>
#include <iostream>

App_window::App_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App_window) {
    temp_chat_id = std::shared_ptr<std::string>(new std::string);
    person_chats = std::shared_ptr<std::vector<Chat>>(new std::vector<Chat>);
    model = std::shared_ptr<QStringListModel>(new QStringListModel);
    model2 = std::shared_ptr<QStringListModel>(new QStringListModel);
    ui->setupUi(this);
    chat_window = new find_chat_window(this);
    connect(chat_window, &find_chat_window::back_to_app, this, &App_window::show);
    connect(chat_window, &find_chat_window::back_to_app, this, &App_window::centrialize);
    connect(chat_window, &find_chat_window::back_to_app, this, &App_window::show_chats);
    connect(this, &App_window::send_person, chat_window, &find_chat_window::set_person);
    ui->chat_creation->hide();
    ui->pushButton_5->hide();
    ui->pushButton_7->hide();
    ui->add_person->hide();
    ui->listView->setEditTriggers(QListView::NoEditTriggers);
    ui->listView_2->setEditTriggers(QListView::NoEditTriggers);
    ui->messages->hide();
}

App_window::~App_window() {
    delete ui;
    delete chat_window;
}

void App_window::refresh_timer()
{
    while(f){
        ui->statusbar->showMessage(rec.time_duration());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void App_window::refresh_messages()
{
    std::string chat_id = *temp_chat_id;
    while(*temp_chat_id == chat_id){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        show_messages(QString::fromStdString(chat_id));
        show_chats();
    }
}

// функция которая вызывается при переходе на это окно
void App_window::set_person(const QString &Login, std::shared_ptr<Client> c) {
    login = Login;
    cl = c;
    ui->profile->show();
    ui->chat_list->hide();
    ui->phone_label->setText(login);
    show_chats();
}


// кнопка профиль -> чаты(сверху слева)
void App_window::on_toolButton_2_clicked() {
    if (ui->toolButton_2->text() == "Профиль") {
        ui->chat_list->hide();
        ui->profile->show();
        ui->toolButton_2->setText("Чаты");
        show_chats();
    } else {
        ui->messages->hide();
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

    rec.record_audio(time);
    voice_file = "./" + time + ".m4a";
    std::thread th(&App_window::refresh_timer, this);
    th.detach();
}

// кнопка записи голосового(отпускается)
void App_window::on_toolButton_3_released()
{
    f = false;
    rec.stop_recording();
    ui->statusbar->clearMessage();
    ui->lineEdit->setText(voice_file);
}


// кнопка отправить
void App_window::on_pushButton_clicked()
{
    std::string text = ui->lineEdit->text().toStdString();
    if(text == "") return;
    if(text.find(".m4a", 0, 1) < text.size() - 1){
        cl.get()->sendVoice(voice_file.toStdString(), *temp_chat_id);
    } else {
        cl.get()->sendMessage(*temp_chat_id, text, ui->phone_label->text().toStdString());
    }
    ui->lineEdit->clear();
    show_messages(QString::fromStdString(*temp_chat_id));
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
    ui->messages->show();
    int id;
    id = ui->listView->currentIndex().row();
    *temp_chat_id = (*person_chats)[id].Id;

    QString chat_name = index.data(0).toString();
    ui->messages->setTitle(chat_name);

        std::thread th(&App_window::refresh_messages, this);
        th.detach();
    show_messages(QString::fromStdString(*temp_chat_id));
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
    *person_chats = cl.get()->get_users_chats(ui->phone_label->text().toStdString());
    QStringList chats;
    for(const auto& chat : *person_chats){
        chats.push_back(QString::fromStdString(chat.chatName));
    }
    model.get()->setStringList(chats);
    ui->listView->setModel(model.get());
}

// функция отображения сообщений
void App_window::show_messages(const QString &chat_id)
{

    std::vector<Message> m = cl.get()->get_last_chat_messages(chat_id.toStdString());

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
    QString path = QString::fromStdString(file_name);
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
    cl.get()->join_chat(*temp_chat_id, ui->lineEdit_5->text().toStdString());
    on_pushButton_7_clicked();
}


// создать чат
void App_window::on_pushButton_4_clicked()
{
    std::vector<std::string> members;
    std::string chat_name = ui->lineEdit_3->text().toStdString();
    std::string member = ui->lineEdit_4->text().toStdString();
    members.push_back(ui->phone_label->text().toStdString());
    if(!member.empty()){
        members.push_back(member);
    }
    cl.get()->create_chat(chat_name, members);
    on_pushButton_5_clicked();
    show_chats();
}

// кнопка присоединиться
void App_window::on_toolButton_5_clicked()
{
    emit send_person(login.toStdString(), cl);
    hide();
    chat_window->show();
}

