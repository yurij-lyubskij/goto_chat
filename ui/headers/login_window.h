#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QStyle>
#include <QtWidgets>
#include <QScreen>

#include "client.h"
#include "checker.h"
#include <QMainWindow>
#include <QString>
#include "app_window.h"
#include "reg_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login_window; }
QT_END_NAMESPACE

class Login_window : public QMainWindow {
    Q_OBJECT

public:

    Login_window(QWidget *parent = nullptr);

    ~Login_window();

    void set_db_name(const QString &name);

//    bool local_check_person(const QString &login, const QString &password);

    bool check_person(const QString &login, const QString &password);

    signals:
    void send_person(const QString &login);

    void window_location();

private slots:
    void on_checkBox_stateChanged(int);

    void on_enter_button_clicked();

    void on_reg_button_clicked();

private:
    void centrialize();

    void clear_lines();

    QString local_db_name;
    Ui::Login_window *ui;
    Reg_window *reg_window;
    App_window *app_window;
};
#endif // LOGIN_WINDOW_H
