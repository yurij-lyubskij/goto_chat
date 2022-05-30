#include "find_chat_window.h"
#include "ui_find_chat_window.h"

find_chat_window::find_chat_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::find_chat_window)
{
    ui->setupUi(this);
}

find_chat_window::~find_chat_window()
{
    delete ui;
}

void find_chat_window::set_person(const std::string &ph, std::shared_ptr<Client> c)
{
    centrialize();
    cl = c;
    phone = ph;
}

void find_chat_window::on_toolButton_clicked()
{
    hide();
    emit back_to_app();
}


void find_chat_window::on_pushButton_clicked()
{
    std::string chat_name = ui->lineEdit->text().toStdString();
    if(chat_name.empty()){
        return;
    }
    model = std::unique_ptr<QStringListModel>(new QStringListModel);
    chats = cl.get()->find_chats(chat_name);
    QStringList chs;
    for(const auto& chat: chats){
        chs.push_back(QString::fromStdString(chat.chatName));
    }
    model.get()->setStringList(chs);
    ui->listView->setModel(model.get());
}



void find_chat_window::on_listView_doubleClicked(const QModelIndex &index)
{
    int id;
    id = ui->listView->currentIndex().row();
    temp_chat_id = chats[id].Id;
    QString chat_name = QString::fromStdString(chats[id].chatName);
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Присоединение к чату", ("Хотетие присоединиться к чату\n" + chat_name + "?"),
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        cl.get()->join_chat(temp_chat_id, phone);
        hide();
        emit back_to_app();
    }
}

// выравнивание окна по центру экрана
void find_chat_window::centrialize()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height() - this->height();
    int width = screenGeometry.width() - this->width();
    this->setGeometry(width / 2, height / 2, this->width(), this->height());
}
