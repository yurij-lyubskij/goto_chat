#ifndef FIND_CHAT_WINDOW_H
#define FIND_CHAT_WINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QScreen>
#include <QMessageBox>
#include <algorithm>
#include "client.h"

namespace Ui {
class find_chat_window;
}

class find_chat_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit find_chat_window(QWidget *parent = nullptr);
    ~find_chat_window();

public slots:
    void set_person(const std::string &ph, std::shared_ptr<Client> c, std::shared_ptr<std::vector<Chat>> p_ch);

signals:
    void back_to_app();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

private:
    void centrialize();
    Ui::find_chat_window *ui;
    std::string phone;
    std::shared_ptr<Client> cl;
    std::unique_ptr<QStringListModel> model;

    std::vector<Chat> chats;
    std::string temp_chat_id;
    std::shared_ptr<std::vector<Chat>> person_chats;
};

#endif // FIND_CHAT_WINDOW_H
