#ifndef REG_WINDOW_H
#define REG_WINDOW_H

#include <QMainWindow>
#include <QScreen>
#include "checker.h"
#include "client.h"

namespace Ui {
class Reg_window;
}

class Reg_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Reg_window(QWidget *parent = nullptr);
    ~Reg_window();

    void registrate();

    bool check_data();

    void centrialize();

signals:
    void login_window();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_2_stateChanged(int);

    void on_checkBox_stateChanged(int);

    void on_pushButton_2_clicked();

private:
    void clear_lines();
    Ui::Reg_window *ui;
};

#endif // REG_WINDOW_H
