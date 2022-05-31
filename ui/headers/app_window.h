#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QScreen>
#include <QStringListModel>
#include <QTableView>
#include <algorithm>
#include <QTime>
#include <mutex>
#include "recorder.h"
#include "client.h"
#include "parser.h"
#include "find_chat_window.h"

namespace Ui {
class App_window;
}

class App_window : public QMainWindow {
    Q_OBJECT

public:
    explicit App_window(QWidget *parent = nullptr);

    ~App_window();

    void open_chat();

    void create_chat();

    void delete_from_chat();

    void leave_chat();

    void reload_chat();

    void send_message();

    void logout();

    void refresh_timer();

    void refresh_messages();

public slots:
    void set_person(const QString &Login, std::shared_ptr<Client> c);

    void centrialize();

signals:
    void login_window();

    void send_person(const std::string &phone, std::shared_ptr<Client> c, std::shared_ptr<std::vector<Chat>> p_ch);

private slots:

    void on_toolButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_toolButton_3_pressed();

    void on_toolButton_3_released();

    void on_pushButton_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_toolButton_clicked();

    void on_pushButton_5_clicked();

    void on_listView_2_doubleClicked(const QModelIndex &index);

    void on_toolButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_toolButton_5_clicked();

private:
    // чаты
    void show_chats();
    std::shared_ptr<QStringListModel> model;

    // сообщения
    void show_messages(const QString& chat_name);
    std::shared_ptr<QStringListModel> model2;

    // для аудио записи и воспроизведения
    std::unique_ptr<QMediaPlayer> player;
    std::shared_ptr<QAudioOutput> audioOutput;
    recorder rec;
    std::atomic_bool f = true;
    QString voice_file;
    void listen_audio(const std::string& file_name);

    // чаты текущего пользователя
    std::shared_ptr<std::vector<Chat>> person_chats;

    // id чата в котором сейчас находится пользователь
    std::shared_ptr<std::string> temp_chat_id;

    // клиент который осуществляет связь с сервером
    std::shared_ptr<Client> cl;

    std::mutex locker;
    // поля этого окна
    find_chat_window* chat_window;
    QString login;
    Ui::App_window *ui;
};

#endif // APP_WINDOW_H
