#ifndef REG_WINDOW_H
#define REG_WINDOW_H

#include <QMainWindow>

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
signals:
    void login_window();

private:
    Ui::Reg_window *ui;
};

#endif // REG_WINDOW_H
