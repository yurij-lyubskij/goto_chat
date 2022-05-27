#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <QMainWindow>
#include "recorder.h"
#include <QTime>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QScreen>
#include "client.h"
#include "parser.h"
#include "QStringListModel"

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

public slots:
    void set_person(const QString &Login);

    void centrialize();

signals:
    void login_window();

private slots:

    void on_toolButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_toolButton_3_pressed();

    void on_toolButton_3_released();

    void on_pushButton_clicked();


    void on_listView_doubleClicked(const QModelIndex &index);

    void on_toolButton_clicked();

    void on_pushButton_5_clicked();

private:
    void show_chats();
    std::unique_ptr<QStringListModel> model;


    std::unique_ptr<QMediaPlayer> player;
    std::shared_ptr<QAudioOutput> audioOutput;
    recorder rec;
    QString login;
    Ui::App_window *ui;
    std::atomic_bool f = true;



};

#endif // APP_WINDOW_H
