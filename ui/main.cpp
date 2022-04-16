#include "login_window.h"
#include "app_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App_window w;
    w.show();
    return a.exec();
}
