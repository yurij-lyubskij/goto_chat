#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <QMainWindow>

namespace Ui {
class App_window;
}

class App_window : public QMainWindow
{
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

public slots:
    void set_person(const QString& Login);
signals:
    void login_window();

private slots:
    void on_commandLinkButton_clicked();

private:
    QString login;
    Ui::App_window *ui;
};

#endif // APP_WINDOW_H
