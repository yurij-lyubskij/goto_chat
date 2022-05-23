#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <QMainWindow>
#include "recorder.h"
#include <QTime>

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


signals:
    void login_window();

private slots:

    void on_toolButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_toolButton_3_pressed();

    void on_toolButton_3_released();

private:
    recorder rec;
    QString login;
    Ui::App_window *ui;
    std::atomic_bool f = true;
};

#endif // APP_WINDOW_H
