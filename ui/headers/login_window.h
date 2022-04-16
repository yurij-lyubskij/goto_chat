#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>
#include <QString>
#include "app_window.h"
#include "reg_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login_window; }
QT_END_NAMESPACE

class Login_window : public QMainWindow
{
    Q_OBJECT

public:

    Login_window(QWidget *parent = nullptr);
    ~Login_window();
    void set_db_name(const QString& name);
    bool local_check_person(const QString& login, const QString& password);
    bool check_person(const QString& login, const QString& password);

signals:
    void send_person(const QString& login);

private:
    QString local_db_name;
    Ui::Login_window *ui;
    Ui::Reg_window* reg_window;
    Ui::App_window* app_window;
};
#endif // LOGIN_WINDOW_H
