#include <QThread>
#include "mainwindow.hpp"
#include "car_joy.h"
#include <QApplication>
#include <QtConcurrent/QtConcurrentRun>

void sendControlData(MainWindow *mw);

int main(int argc, char *argv[])
{
    if (init_sock(81, "192.168.4.1") != 0) {
        return -1;
    }

    QApplication app(argc, argv);
    MainWindow window;
    QFuture<void> car_joy_future = QtConcurrent::run(sendControlData, &window);

    window.show();
    return app.exec();
}

void sendControlData(MainWindow *mw)
{
    while(1) {
        if (mw->getJoyFd() >= 0)
        {
            ssize_t written = send_data(stick_joy, mw->getJoyFd());
        }
    }
}

