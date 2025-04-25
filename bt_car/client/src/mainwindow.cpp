#include "mainwindow.hpp"
//#include "car_joy.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QCameraInfo>
#include <QVideoWidget>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <iostream>
#include "camera.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), joyFd(-1),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    joyPortsGroup = new QActionGroup(this);

    setupMenuConnections();

    QLabel *video = ui->centralwidget->findChild<QLabel*>();
    QThread* thread = new QThread;
    EspCamera* stream = new EspCamera(video);
    stream->moveToThread(thread);
    connect(thread, &QThread::started, [stream]() { stream->startStream(QUrl("http://192.168.4.1/stream")); });
    thread->start();
}


MainWindow::~MainWindow()
{
    if (joyFd >= 0) ::close(joyFd);

    workerThread.quit();
    workerThread.wait();
    delete ui;
}

ssize_t MainWindow::getJoyFd() {
    return this->joyFd;
}

void MainWindow::setupMenuConnections()
{
    connect(ui->menujoy, &QMenu::aboutToShow, this, &MainWindow::refreshJoyPorts);
}

void MainWindow::refreshJoyPorts()
{
    QMenu* menu = qobject_cast<QMenu*>(sender());
    QDir dir("/dev/input");
    QStringList files = dir.entryList(QStringList("js*"), QDir::System);
    updateMenuActions(menu, joyPortsGroup, files, std::function<void()>(std::bind(&MainWindow::handleJoyPortSelection, this)));
}

void MainWindow::updateMenuActions(QMenu* menu, QActionGroup* group, const QStringList& items, const std::function<void()>& handler)
{
    foreach (QAction* action, group->actions()) {
        if (!items.contains(action->text())) {
            menu->removeAction(action);
            group->removeAction(action);
            action->deleteLater();
        }
    }

    foreach (const QString& item, items) {
        bool exists = false;
        foreach (QAction* action, group->actions()) {
            if (action->text() == item) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            QAction* action = new QAction(item, this);
            action->setCheckable(true);
            group->addAction(action);
            menu->addAction(action);

            connect(action, &QAction::triggered, this, [handler](bool) {
                handler();
            });
        }
    }
}

void MainWindow::handleJoyPortSelection()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (!action) return;

    QString devicePath = "/dev/input/" + action->text();
    ui->statusbar->showMessage(devicePath);

    if (joyFd >= 0) ::close(joyFd);
    joyFd = open(devicePath.toStdString().c_str(), O_RDONLY);

    if (joyFd < 0) {
        fprintf(stderr, "Failed to open joystick device(%s): %s\n", devicePath.toUtf8().constData(), strerror(errno));
    }
}

